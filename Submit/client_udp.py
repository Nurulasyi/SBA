import socket

def udp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = ('localhost', 5000)

    range_start = int(input('Enter the starting number: '))
    range_end = int(input('Enter the ending number: '))

    for num in range(range_start, range_end + 1):
        client_socket.sendto(str(num).encode(), server_address)
        result, _ = client_socket.recvfrom(1024)
        print(result.decode())

    client_socket.close()

udp_client()

