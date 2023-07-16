import socket

def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def tcp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('', 5010)  # Empty string for localhost
    server_socket.bind(server_address)
    server_socket.listen(1)
    print('TCP server is running.')

    while True:
        connection, client_address = server_socket.accept()
        print('Connected to:', client_address)

        try:
            while True:
                data = connection.recv(1024)
                if not data:
                    break
                num = int(data.decode())
                
                if is_prime(num):
                    result = f'{num} is a prime number.'
                else:
                    result = f'{num} is not a prime number.'

                connection.sendall(result.encode())
        except Exception as e:
            print('Error:', str(e))

        connection.close()

tcp_server()

