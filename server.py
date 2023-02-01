from faker import Faker
import asyncio
import websockets
import names

async def send_messages(websocket):
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