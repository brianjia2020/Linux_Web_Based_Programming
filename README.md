this is a course for web based programming for linux.

# 1. TCP/IP
# 2. UDP client/server 



Notes:
  C/S architcture
  server: socket() -> bind() -> recvfrom() -> sendto()
  client: socket() -> sendto() -> recvfrom() -> close()

  3 main issues to resolve for network communication:
  protocol, ip, port
  we used struct socketaddr_in
