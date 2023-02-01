import asyncio
import websockets
import time


async def send_messages(websocket, start_time, seq_num):
        response = f"Client3 received {seq_num} block in {time.time() - start_time} time"
        await websocket.send(response)
        await asyncio.sleep(1)

async def receive_messages(websocket):
    data_block = []
    async for message in websocket:
        data_block.append(message)
        if len(data_block) == 5:
            break
    return data_block

async def main():
    seq_num = 1
    while True :
        try :
            async with websockets.connect("ws://localhost:8000") as websocket:
                start_time = time.time()
                data_block = await receive_messages(websocket)
                await send_messages(websocket, start_time, seq_num)
                seq_num += 1
        except websockets.exceptions.ConnectionClosedError:
            print("Server connection lost, trying to reconnect...")
            await asyncio.sleep(5)
        except ConnectionRefusedError :
            print("Server connection lost, trying to reconnect...")
            await asyncio.sleep(5)

asyncio.run(main())

