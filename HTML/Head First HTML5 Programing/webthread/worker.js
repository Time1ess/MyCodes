onmessage=pingPong;

function pingPong(event)
{
    if(event.data=="ping")
    {
        postMessage("pong");
    }
}

