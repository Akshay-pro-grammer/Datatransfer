Absolutely — here is a clean, professional, and presentation-ready description you can paste directly into your official document.
This explains the local media server architecture, how discovery works, and how the TV streams content — in a way that is understandable to both engineers and managers.


---

📘 Local Media Server Architecture — Technical Overview

1. Introduction

The Local Media Server feature enables any laptop on the same Wi-Fi network as the LG webOS TV to act as a lightweight media provider.
The laptop runs a small Node.js application that:

1. Scans a folder for videos


2. Broadcasts its availability using mDNS


3. Provides a simple HTTP API to list media files


4. Streams video content directly to the TV



This setup allows the webOS Media Discovery application to automatically detect laptop servers on the LAN and play their media — similar to a simplified local Plex server.


---

2. High-Level Architecture

The architecture contains two main components:

A. Laptop Media Server (Node.js)

Hosts media content

Shares metadata via a REST API

Streams raw video over HTTP

Advertises itself using mDNS/Bonjour


B. Media Discovery App (webOS TV)

Listens for local mDNS services

Fetches media list from discovered server

Initiates video playback using server’s streaming endpoint


Both devices communicate over the same local network using IPv4.


---

3. Laptop Media Server – Internal Components

3.1 Folder Scanner

Monitors a predefined directory (/videos/)

Generates a list of available video files

Provides metadata:

id

name

file path



This list is returned as JSON to the TV.


---

3.2 HTTP REST API

The server exposes two core endpoints:

1. GET /media

Returns a list of files:

[
  { "id": 0, "name": "movie1.mp4" },
  { "id": 1, "name": "video2.mp4" }
]

2. GET /stream/:id

Streams video in chunks

Supports byte-range requests (seek, pause/play)

Compatible with LG’s HTML5 WebOS video player


This allows seamless playback even for large files.


---

3.3 Video Streaming Logic

The server reads video files in 1–10 MB chunks and responds using HTTP 206 Partial Content with headers:

Content-Range

Accept-Ranges

Content-Length

Content-Type: video/mp4


This allows:

Seeking

Progressive loading

Smooth playback



---

3.4 mDNS/Bonjour Broadcast

The server advertises itself as an HTTP device on the LAN:

Service Type:  _http._tcp.local
Service Name:  LaptopMediaServer
Port:          9000

Any WebOS device listening to mDNS queries can automatically discover the laptop without requiring manual IP configuration.


---

4. WebOS TV – Discovery & Playback Flow

Step 1 — Discovery

The Media Discovery app listens for mDNS announcements.
When the laptop broadcasts:

LaptopMediaServer._http._tcp.local

The TV receives the advertisement with:

Device name

IP address

Port number


This server then appears in the Media Discovery device list.


---

Step 2 — Fetching Media List

When the user selects the laptop, the TV sends:

GET http://<laptop-ip>:9000/media

The server returns JSON with all video files.


---

Step 3 — Displaying Media

The TV renders this list as thumbnails/titles.


---

Step 4 — Streaming

On selecting a particular video, the TV requests:

GET http://<laptop-ip>:9000/stream/<id>

The server streams the video using range-based HTTP streaming, and the content is played using the TV’s native video player.


---

5. Advantages of This Approach

✔ No configuration required

Auto-discovery via mDNS means users don’t need to know IP addresses.

✔ Very lightweight

Requires no database, no transcoding engine, no heavy dependencies.

✔ Secure (local-only)

Data never leaves the local network.

✔ Fast and reliable

Direct LAN streaming avoids buffering and bandwidth issues.

✔ Compatible with future remote-access tunneling

This architecture becomes the foundation for Phase 2 (cloud relay/tunneling).


---

6. Data Flow Summary

┌───────────────────────────────────────────┐
│             Laptop Media Server           │
│  - Node.js HTTP streaming server          │
│  - Broadcast via mDNS                     │
└───────────────┬───────────────────────────┘
                │ mDNS Advertisement
                ▼
┌───────────────────────────────────────────┐
│          WebOS Media Discovery App        │
│ - Auto-detects server via mDNS            │
│ - Calls /media to get video list          │
│ - Streams using /stream/<id>              │
└───────────────────────────────────────────┘


---

7. Conclusion

This local media server architecture provides a simple yet powerful foundation for media sharing within a home network. The combination of:

mDNS for zero-configuration discovery

HTTP APIs for lightweight control

Range-based streaming for compatibility


makes the system easy to implement, demo, and extend.

This forms the base layer for the next phase — a tunneling-based remote media server, which will allow WebOS TVs outside the home network to access the same content securely.


---

If you want, I can now generate:

📄 A polished PDF-style document
📊 A proper architecture diagram (SVG / PNG)
📐 Sequence diagrams
📝 API documentation

Just tell me!
