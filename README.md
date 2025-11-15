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
├── client.cpp # client implementation
└── README.md # Project documentation

---

## ▶️ Usage
medius --server <port>
eg. medius --server 8080
medius --client <ip> <port>
eg. medius --client 127.0.0.1 8080

---

## 📸 Working Screenshots

1. Medius server started on port 5678.
   <img width="725" height="169" alt="image" src="https://github.com/user-attachments/assets/9c4d1833-f9a4-4bd0-84a6-9f733ad51adf" />
2. Medius client 1 connecting to server running on 192.168.33.230
   <img width="1049" height="239" alt="image" src="https://github.com/user-attachments/assets/4a5d5097-1e15-4ffd-bbab-0abe45714006" />
3. Medius client 2 connecting to server running on 192.168.33.230
   <img width="658" height="176" alt="image" src="https://github.com/user-attachments/assets/a7d50aa7-a736-4b10-a922-6b3f552c98ea" />


   
## ⚙️ How It Works

1. The server creates a **TCP socket** on port `8080`.
3. When any client sends a message, the server **broadcasts** it to all others.
4. The server runs in a **non-blocking** loop using `select()` (no threads required).

---

## 💻 Build Instructions

### 🪟 **Windows (MSVC)**
Use the **Developer Command Prompt for Visual Studio**:

```bash
cl /EHsc main.cpp server.cpp /Fe:server.exe


