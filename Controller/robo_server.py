import asyncore


class DataHandler(asyncore.dispatcher_with_send):

    def handle_read(self):
        bytes = self.recv(1)
        size = int.from_bytes(bytes, byteorder='big')

        if size is not 0:
            data = self.recv(size)
            print(data)


class RoboServer(asyncore.dispatcher):

    def __init__(self, host, port):
        asyncore.dispatcher.__init__(self)
        self.create_socket()
        self.set_reuse_addr()
        self.bind((host, port))
        self.listen(5)

    def handle_accepted(self, sock, addr):
        print('Incoming connection from %s' % repr(addr))
        handler = DataHandler(sock)



server = RoboServer('localhost', 8080)
asyncore.loop()