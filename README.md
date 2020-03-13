# MultiplayerPong
A simple pong game, but networked.

## Build

You'll need to build both in the `server` directory and the `client` directory.
There is a Makefile in each.

```
1. cd client/
2. make
3. cd server/
4. make
```

## Run

**You must start the server first**.  Then start two client programs. So, open 3 terminal windows.

```
1. cd server/
2. ./multiplayerpong (terminal 1)
3. cd client/
4. ./multiplayerpong (terminal 2)
5. ./multiplayerpong (terminal 3)
```

![PONG](/pong-action.png)
