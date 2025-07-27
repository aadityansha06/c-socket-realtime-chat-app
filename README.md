# 🧑‍💻 C Socket Realtime Chat App (Windows)

This is a simple real-time chat application implemented in C using **sockets and multithreading** (Windows Winsock API). It demonstrates basic client-server communication over TCP sockets, similar to a terminal-based messenger.

## 🔧 Features

- Client-server architecture using TCP (IPv4)
- Real-time 2-way messaging with multithreading
- Graceful connection close with `exit` command
- ANSI C + Windows-only (uses `winsock2.h` and `_beginthread`)


---

## ⚙️ Requirements

- Windows OS
- GCC compiler (e.g., via MinGW or Dev-C++)
- CMD or Windows Terminal

---

## 🛠️ How to Build and Run

### 🖥️ Server

```bash
gcc server.c -o server.exe -lws2_32
./server.exe
````
Compile 💻 Client_side
````bash
gcc client.c -o client.exe -lws2_32
./client.exe
````


📌 On client startup, you will be asked to enter the server IP (e.g., 127.0.0.1 for localhost).
You can chnage the code to IpV6 for Online or with other user interaction 

💬 Example Demo
Terminal 1 – Server

waiting for connection.. at port 9090
connected successfully.. from IP 127.0.0.1
Send message ...       Hello from server!

Terminal 2 – Client

Enter the ip to connect...   127.0.0.1
Connected successfully.. to server127.0.0.1
        Host: Hello from server!
Send message ...       Hello from client!


Use exit to quit the chat gracefully.

🧠 How It Works
The server binds to port 9090 and listens for incoming connections.

The client connects to the server using the given IP.

After connection:

Server and client both launch two threads:

One for receiving (recv())

One for sending (send())

The loop runs until either side sends "exit".


❗ Notes
This code uses blocking sockets, so each thread handles one direction of communication.

Only works on Windows due to winsock2.h and _beginthread().

Doesn't support multiple clients (one-to-one chat only).

Be sure to compile with -lws2_32 to link Windows Socket library.
<br>
🔗 <h3>Contact</h3><br>
📬 Follow or DM me on X (Twitter): @aadityansha_06 <br>
Dm on telegram : Aadityansha


### <br>
<h3>🙌 Credits</h3>
<br>
Made with 💻 and a lot of effort by @aadityansha06

