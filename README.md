# 🛰️ Medius Multi-Client Broadcast Server (C++)

A cross-platform **TCP broadcast server** built in **C++**, allowing multiple clients to connect simultaneously.  
Whatever the server sends (or receives) is broadcasted to all connected clients — ideal for chat, messaging, or telemetry systems.

---

## 🚀 Features

✅ Supports **multiple client connections**  
✅ **Broadcasts messages** from server to all clients  
✅ **Cross-platform** — works on **Windows** and **Linux**  
✅ Clean OOP design (`Server` class)  
✅ No external libraries — only standard sockets API  
✅ Graceful client disconnect handling  

---

## 🏗️ Project Structure
Medius
├── server.h # Server class declaration
├── server.cpp # Server class implementation
├── main.cpp # Entry point to start the server
├── client.cpp # (optional) client implementation
└── README.md # Project documentation

---

## ⚙️ How It Works

1. The server creates a **TCP socket** on port `8080`.
2. Multiple clients can connect using `telnet`, `netcat`, or a custom C++ client.
3. When any client sends a message, the server **broadcasts** it to all others.
4. The server runs in a **non-blocking** loop using `select()` (no threads required).

---

## 💻 Build Instructions

### 🪟 **Windows (MSVC)**
Use the **Developer Command Prompt for Visual Studio**:

```bash
cl /EHsc main.cpp server.cpp /Fe:server.exe


