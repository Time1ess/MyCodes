var numberOfWorkers=8;
var workers=[];

window.onload=init;

function init()
{
    setupGraphics();
    /*window.onresize=function()
    {
        resizeToWindow();
    }*/
    canvas.onclick=function(event)
    {
        handleClick(event.clientX,event.clientY);
    }

    for(var i=0;i<numberOfWorkers;i++)
    {
        var worker=new Worker("worker.js");
        
        worker.onmessage=function(event)
        {
            processWork(event.target,event.data);
        }

        worker.idle=true;

        workers.push(worker);

    }

    startWorkers();
}

var nextRow=0;
var generation=0;

function startWorkers()
{
    generation++;
    nextRow=0;

    for(var i=0;i<workers.length;i++)
    {
        var worker=workers[i];

        if(worker.idle)
        {
            var task=createTask(nextRow);

            worker.idle=false;
            worker.postMessage(task);

            nextRow++;
        }
    }
}

function processWork(worker,workerResults)
{
    if(workerResults.generation==generation)
    drawRow(workerResults);
    reassignWorker(worker);
}

function reassignWorker(worker)
{
    var row=nextRow++;

    if(row>=canvas.height)
    {
        worker.idle=true;
    }
    else
    {
        var task=createTask(row);
        worker.idle=false;
        worker.postMessage(task);
    }
}

function handleClick(x,y)
{
    var width=r_max-r_min;
    var height=i_min-i_max;
    var click_r=r_min+width*x/canvas.width;
    var click_i=i_max+height*y/canvas.height;

    var zoom=8;

    r_min=click_r-width/zoom;
    r_max=click_r+width/zoom;
    i_max=click_i-height/zoom;
    i_min=click_i+height/zoom;

    startWorkers();
}

function resizeToWindow()
{
    canvas.width=window.innetWidth;
    canvas.height=window.innerHeight;
    var width=((i_max-i_min)*canvas.width/canvas.height);
    var r_mid=(r_max+r_min)/2;
    r_min=r_mid-width/2;
    r_max=r_mid+width/2;
    rowData=ctx.createImageData(canvas.width,1);

    startWorkers();
}
