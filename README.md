# Embedathon-2023

How to run the files
1. Run the file server.py which runs the websocket server that send and then receive messages
2. Then run client files (client1.py, client2.py ,client3.py) which receive and then send messages to the server.

Module Used:
1. asyncio : Asyncio is a library for asynchronous I/O in Python. It's used in server-client websocket applications to handle multiple clients simultaneously, allowing for efficient and scalable communication between the server and clients. This is achieved by using asynchronous programming techniques, where long-running tasks are executed in the background, allowing the main thread to handle other incoming requests without getting blocked. This results in faster and more responsive communication, which is especially important for real-time applications like websockets.

2. Websocket : The websocket module is used in server-client websocket applications to facilitate communication between the server and clients. The websocket protocol is a standard for real-time, bi-directional communication between clients and servers over a single, long-lived connection. The websocket module implements this protocol, providing a simple and efficient way to establish and maintain websocket connections between the server and clients.

3. Time : It can be used to track the duration of a connection or the time at which a message was sent or received. In a websocket application, the time module can be used to implement timeouts, to schedule periodic updates, or to enforce certain timing constraints in the communication between the server and clients.

#server.py

from faker import Faker
import asyncio
import websockets
import names

async def send_messages(websocket): #function to send random message
    while True:
        await websocket.send(names.get_full_name())
        await asyncio.sleep(1)

async def receive_messages(websocket):
    while True:
        message = await websocket.recv()
        print(message)


async def server(websocket, path):
    # Create tasks to send and receive messages concurrently
    send_task = asyncio.create_task(send_messages(websocket))
    receive_task = asyncio.create_task(receive_messages(websocket))
    await asyncio.gather(send_task, receive_task)


async def main():
    # Start the server
    async with websockets.serve(server, "localhost", 8000):
        await asyncio.Future()

asyncio.run(main())

#client.py



Output:
![Screenshot from 2023-02-01 23-32-13](https://user-images.githubusercontent.com/82582574/216126061-f51cbef6-d524-4755-9d5c-c7b40aff70d5.png)
![Screenshot from 2023-02-01 23-32-18](https://user-images.githubusercontent.com/82582574/216126075-f0355a32-5047-4595-b62f-d4d6206df385.png)
![Screenshot from 2023-02-01 23-32-24](https://user-images.githubusercontent.com/82582574/216126082-4e8b22f4-a08c-455d-b14c-12fd830a3240.png)
![Screenshot from 2023-02-01 23-32-58](https://user-images.githubusercontent.com/82582574/216126090-143e593d-0925-4e28-b5de-071a003d78c4.png)
![Screenshot from 2023-02-01 23-33-04](https://user-images.githubusercontent.com/82582574/216126095-e472ad23-0f60-4290-965b-27921707247e.png)
