#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>

// create socket, bind, listen
// loop to continue
  // create processes for client socket
// close socket

int main(int argc, char const *argv[])
{
  /* code */
  // add SIGCHILD to block list
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGCHLD);
  sigprocmask(SIG_BLOCK, &set, sizeof(set));

  // step 1. create socket
  int s_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (s_fd < 0) 
    perror("server socket failed");
  
  // step 2. bind
  struct sockaddr_in myaddr;
  myaddr.sin_family = AF_INET;
  myaddr.sin_port = htons(9999);
  myaddr.sin_addr.s_addr = 0; // bind all local ip
  bind(s_fd, (struct sockaddr*)&myaddr, sizeof(myaddr));

  // step 3. listen
  listen(s_fd, 128);

  // step 4. loop
  struct sockaddr_in cli_addr;
  socklen_t len = sizeof(cli_addr);
  while(1) {
    int c_fd = accept(s_fd, (struct sockaddr*)&cli_addr, &len);
    if (c_fd < 0) {
        perror("accept failed.");
    }
    char ip[INET_ADDRSTRLEN] = "";
    printf(
        "client ip=%s, port=%d\n", 
        inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, ip, INET_ADDRSTRLEN),
        ntohs(cli_addr.sin_port));
    pid_t pid;
    pid = fork();
    if (pid  == 0) { // child process
      while(1) {
        close(s_fd);
        char buf[256] = "";
        int n = read(c_fd, buf, sizeof(buf));
        if (n == 0) {
          printf("client closed!\n");
          break;
        }
        printf("received: %s\n", buf);
        write(c_fd, buf, n); // send back
      }
      break;
    } else if (pid > 0) {
      close(c_fd);
      struct sigaction act;
      act.__sigaction_u.__sa_handler = &catch_child;
      act.sa_flags = 0;
      sigemptyset(&act.sa_mask);
      sigaction(SIGCHLD, &act, NULL);

      sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
  }
  return 0;
}

