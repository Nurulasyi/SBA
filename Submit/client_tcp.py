import socket

def tcp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 5010)
    client_socket.connect(server_address)

    range_start = int(input('Enter the starting number: '))
    range_end = int(input('Enter the ending number: '))

    for num in range(range_start, range_end + 1):
        client_socket.sendall(str(num).encode())
        result = client_socket.recv(1024)
        print(result.decode())

    client_socket.close()

tcp_client()

