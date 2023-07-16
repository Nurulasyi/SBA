import socket

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('', 5000)  # Empty string for localhost
    server_socket.bind(server_address)
    print('UDP server is running.')

    while True:
        data, client_address = server_socket.recvfrom(1024)
        num = int(data.decode())

        if is_prime(num):
            result = f'{num} is a prime number.'
        else:
            result = f'{num} is not a prime number.'

        server_socket.sendto(result.encode(), client_address)

udp_server()

