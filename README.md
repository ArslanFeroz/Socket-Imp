# C++ Client-Server Networking (PNet)

This project is a simple **client-server networking application in C++** built using a custom networking library called **PNet**.

It demonstrates socket programming concepts including:
- TCP communication
- Client-server architecture
- Custom abstraction over low-level sockets

---

## Project Structure

New/
├── Client/
│   └── Source.cpp        -> Client-side code
├── Server/
│   └── Source.cpp        -> Server-side code
└── Pnet/                 -> Custom networking library
    ├── Socket.cpp / .h
    ├── Network.cpp / .h
    ├── IPEndPoint.cpp / .h
    ├── SocketHandle.h
    ├── SocketOption.h
    ├── IpVersion.h
    ├── PResult.h
    └── IncludeMe.h

---

## Features

- Custom socket wrapper (PNet)
- TCP client-server communication
- Clean abstraction over OS-level sockets
- Modular code structure
- Cross-file organization (Client, Server, Library)

---

## Requirements

- C++ compiler (g++)
- Linux / Ubuntu (recommended)

---

## How to Compile

### Compile Server

```bash
g++ Server/Source.cpp Pnet/*.cpp -o server
```

### Compile Client

```bash
g++ Client/Source.cpp Pnet/*.cpp -o client
```

---

## How to Run

### Step 1: Start Server

```bash
./server
```

### Step 2: Run Client (in another terminal)

```bash
./client
```

---

## How It Works

1. Server initializes networking and waits for connections.
2. Client connects to server using IP and port.
3. Messages are exchanged between client and server.
4. Communication continues until closed.

---

## Key Components

### PNet Library

- `Socket` → Handles socket operations
- `Network` → Initializes networking system
- `IPEndPoint` → Stores IP and port
- `PResult` → Error/result handling

---



## Future Improvements

- Add UDP support
- Add multi-client handling (threads)
- Improve error handling
- GUI interface

---

