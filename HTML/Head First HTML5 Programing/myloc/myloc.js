window.onload=getMyLocation;

function getMyLocation(){
    if(navigator.geolocation){
        //navigator.geolocation.getCurrentPosition(displayLocation,displayError);
        var watch_button=document.getElementById("watch");
        watch_button.onclick=watchLocation;
        var clear_watch_button=document.getElementById("clearWatch");
        clear_watch_button.onclick=clearWatch;
        
    }
    else{
        alert("Oops,no geolocation support!");
    }
}

function displayLocation(position){
    var latitude=position.coords.latitude;
    var longitude=position.coords.longitude;
    var div=document.getElementById("location");
    div.innerHTML="You are at Latitude: "+latitude+", Longitude: "+longitude;
    div.innerHTML+=" (with "+position.coords.accuracy+" meters accuracy";

    var km=computeDistance(position.coords,OUR_COORDS);
    var distance=document.getElementById("distance");
    distance.innerHTML="You are "+km+" km from the WickedlySmart HQ";

    if(map==null)
        showMap(position.coords);
    else
        scrollMapToPosition(position.coords);
}
function displayError(error){
    var error_types={
        0:"Unknown error",
        1:"Permission denied by user",
        2:"Position is not available",
        3:"Request timed out"
    };
    var error_message=error_types[error.code];
    if(error.code==0||error.code==2){
        error_message=error_message+" "+error.message;
    }
    var div=document.getElementById("location");
    div.innerHTML=error_message;
}
function computeDistance(start_coords,dest_coords){
    var start_lat_rads=degreesToRadians(start_coords.latitude);
    var start_long_rads=degreesToRadians(start_coords.longitude);
    var dest_lat_rads=degreesToRadians(dest_coords.latitude);
    var dest_long_rads=degreesToRadians(dest_coords.longitude);

    var RADIUS=6371;
    var distance=Math.acos(Math.sin(start_lat_rads)*Math.sin(dest_lat_rads)+
            Math.cos(start_lat_rads)*Math.cos(dest_lat_rads)*
            Math.cos(start_lat_rads-dest_lat_rads))*RADIUS;

    return distance;
}

function degreesToRadians(degrees){
    var radians=(degrees*Math.PI)/180;
    return radians;
}
var OUR_COORDS={
    latitude:47.624851,
    longitude:-122.52099
};

var map;

function showMap(coords){
    var google_lat_and_long=
        new google.maps.LatLng(coords.latitude,coords.longitude);
    var map_options={
        zoom: 10,
        center: google_lat_and_long,
        mapTypeId: google.maps.MapTypeId.HYBRID
    };
    var map_div=document.getElementById("map");
    map=new google.maps.Map(map_div,map_options);
    
    var title="Your Location";
    var content="You are here: "+coords.latitude+", "+coords.longitude;
    addMarker(map,google_lat_and_long,title,content);
}
function addMarker(map,latlong,title,content){
    var marker_options={
        position:latlong,
        map:map,
        title:title,
        clickable:true
    };
    var marker=new google.maps.Marker(marker_options);

    var info_window_options={
        content:content,
        position:latlong
    };
    var info_window=new google.maps.InfoWindow(info_window_options);

    google.maps.event.addListener(marker,"click",function(){
        info_window.open(map);
    });
}

var watch_id=null;
var last_time_out=0;
function watchLocation(){
    last_time_out+=100;
    watch_id=navigator.geolocation.watchPosition(
            displayLocation,displayError,
            {
                timeout:last_time_out,
                maximumAge:0,
                enableHighAccuracy:true
            });
}

function clearWatch(){
    if(watch_id){
        navigator.geolocation.clearWatch(watch_id);
        watch_id=null;
    }
}
function scrollMapToPosition(coords){
    var latitude=coords.latitude;
    var longitude=coords.longitude;
    var latlong=new google.maps.LatLng(latitude,longitude);

    map.panto(latlong);

    addMarker(map,latlong,"Your new location","You moved to: "+latitude+", "+longitude);
}
