<head>
<link rel=preconnect href=https://wasm.noahcohn.com>
<link rel=preconnect href=https://js.1ink.us>
<link rel=preconnect href=https://glsl.1ink.us>
<link rel=preconnect href=https://css.1ink.us>
<title>R*A*1*N</title>
<link crossorigin rel='stylesheet' href='https://css.1ink.us/sh1.1iss'>
<link rel='stylesheet' href='./css/normalize.css'>
<link href='https://fonts.googleapis.com/css?family=Roboto:400,100,300,700,500,900' rel='stylesheet'>
<link rel='stylesheet' href='./css/demo.css'>
<link rel='stylesheet' href='./css/style1.css'>
<link rel='stylesheet' href='./mono-index.css'>
</head>
<body class=demo-1>
<nav id=menu>
<section class=menu-section id=menu-sections>
<br>
<div style=text-align:center;>
TIMESLIDER<br>(Seconds between video change)</div>
<br><br>
<ul class=menu-section-list>
<div id=mnu>
<div id=slideframe>
<input type=text id=timeslider></input>
</div></div></ul></section></nav>
<main id=panel>
<div class=image-preload>
<img src=./img/drop-color.png alt=''>
<img src=./img/drop-alpha.png alt=''>
<img src=./img/weather/texture-rain-fg.png>
<img src=./img/weather/texture-rain-bg.png>
<img src=./img/weather/texture-sun-fg.png>
<img src=./img/weather/texture-sun-bg.png>
<img src=./img/weather/texture-fallout-fg.png>
<img src=./img/weather/texture-fallout-bg.png>
<img src=./img/weather/texture-drizzle-fg.png>
<img src=./img/weather/texture-drizzle-bg.png>
</div>
<link rel="stylesheet" href="./mono-index.css" />
</head>
<body>
<div id="container" style="width: 800px; height: 600px; border: 1px solid #ccc"></div>
<script type="module" src="./mono-index.js"></script>
<header class=codrops-header>
<h1>Rain &amp; Water Effects</h1>
<nav class=codrops-demos>
<a class=current-demo href=./index.html  style='position:absolute;top:0;z-index:999996;'>Weather</a>
<a href=./index2.html>Water</a>
<a href=./index3.html>Video</a>
</nav>
</header>
<div class=slideshow style='position:absolute;top:0;z-index:999994;'>
<canvas width=1 height=1 id=container style='position:absolute;top:0;z-index:999995;'></canvas>
<div class=slide id=slide-1 data-weather=rain>
<div class='slide__element slide__element--date'>Sunday, 24<sup>th</sup> of October 2043</div>
<div class='slide__element slide__element--temp'>12Â°<small>C</small></div>
</div>
<div class=slide id=slide-2 data-weather=drizzle>
<div class='slide__element slide__element--date'>Saturday, 25<sup>th</sup> of October 2043</div>
<div class='slide__element slide__element--temp'>18Â°<small>C</small></div>
</div>
<div class=slide id=slide-3 data-weather=sunny>
<div class='slide__element slide__element--date'>Monday, 26<sup>th</sup> of October 2043</div>
<div class='slide__element slide__element--temp'>25Â°<small>C</small></div>
</div>
<div class=slide id=slide-5 data-weather=storm>
<div class='slide__element slide__element--date'>Wednesday, 28<sup>th</sup> of October 2043</div>
<div class='slide__element slide__element--temp'>20Â°<small>C</small></div>
</div>
<div class=slide id=slide-4 data-weather=fallout>
<div class='slide__element slide__element--date'>Tuesday, 27<sup>th</sup> of October 2043</div>
<div class='slide__element slide__element--temp'>34Â°<small>C</small></div>
</div>
<nav class=slideshow__nav>
<a class=nav-item href=#slide-1><i class='icon icon--rainy'></i><span>10/24</span></a>
<a class=nav-item href=#slide-2><i class='icon icon--drizzle'></i><span>10/25</span></a>
<a class=nav-item href=#slide-3><i class='icon icon--sun'></i><span>10/26</span></a>
<a class=nav-item href=#slide-5><i class='icon icon--storm'></i><span>10/28</span></a>
<a class=nav-item href=#slide-4><i class='icon icon--radioactive'></i><span>10/27</span></a>
</nav>
</div>
<iframe src=./bezz.1ink style='pointer-events:none;border-width:0px;position:absolute;top:0px;left:0px;right:0px;bottom:0px;overflow:hidden;z-index:999998;display:block;overflow-y:hidden;overflow-x:hidden;' id=circle title='Circular mask'></iframe>
<input type=button id=btn1 style='background-color:black;position:absolute;display:block;left:5%;top:50%;z-index:999999;border:5px solid #e7e7e7;border-radius:50%;'></input>
<input type=button id=btn3 style='background-color:purple;position:absolute;display:none;left:3%;top:13%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di")).click();'></input>
<input type=button id=btn style='background-color:blue;position:absolute;display:none;left:3%;top:23%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di")).click();'></input>
<input type=button id=btn2 style='background-color:white;position:absolute;display:none;left:3%;top:3%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di")).click();'></input>
<input type=button id=btn9 style='background-color:tan;position:absolute;display:none;left:5%;top:3%;z-index:999997;border:5px solid red;border-radius:50%;'></input>
<input type=button id=btn10 style='background-color:purple;position:absolute;display:none;left:8%;top:3%;z-index:999997;border:5px solid red;border-radius:50%;'></input>
<input type=button id=btn4 style='background-color:grey;position:absolute;display:none;left:3%;top:33%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di").click();'></input>
<input type=button id=btn11 style='background-color:green;position:absolute;display:none;left:7%;top:33%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di").click();'></input>
<input type=button id=btn5 style='background-color:pink;position:absolute;display:none;left:3%;top:43%;z-index:999997;border:5px solid red;border-radius:50%;' onclick='document.getElementById("di").click();'></input>
<input type=button id=btn6 style='background-color:yellow;position:absolute;display:none;left:3%;top:53%;z-index:999997;border:5px solid red;border-radius:50%;'></input>
<input type=button id=btn7 style='background-color:black;position:absolute;display:none;left:3%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;'></input>
<input type=button id=btn77 style='background-color:tan;position:absolute;display:none;left:7%;top:63%;z-index:999997;border:5px solid red;border-radius:50%;'></input>
<input type=button id=btn8 style='background-color:cyan;position:absolute;display:block;left:3%;top:73%;z-index:999999;border:5px solid green;border-radius:50%;'></input>
<div class=emscripten id=status>|Loading WASM|</div>
<div class=emscripten>
<progress value=0 max=100 id=progress></progress>
</div>
<input type=checkbox id=di hidden/>
<div hidden=true id=path>./drops</div>
<div id=iwid hidden>0</div>
<div id=ihig hidden>0</div>
<div id=pmhig hidden>1080</div>
<div id=wid hidden>0</div>
<div id=hig hidden>0</div>
<div id=ihid hidden>0</div>
<div id=tim hidden>5000</div>
<div id=shut hidden>1</div>
<div id=isrc hidden>./intro.mp4</div>
<div id=idur hidden>0</div>
<div id=itim hidden>0</div>
<div id=wrap>
<div id=contain1>
<canvas id=scanvas class=emscripten style='opacity:0.333;pointer-events:none;display:block;position:absolute;z-index:999997;background-color:rgba(1,1,1,0);top:0;height:100vh;width:100vh;image-rendering:auto;'></canvas>
</div>
<div id=contain2>
<canvas id=acanvas style='pointer-events:auto;cursor:url(cursor.cur),auto;display:block;z-index:999996;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
<canvas id=bcanvas style='pointer-events:none;display:block;z-index:999995;position:absolute;height:100vh;width:100vh;margin-left:auto;margin-right:auto;background-color:rgba(1,1,1,0);top:0;image-rendering:auto;'></canvas>
</div>
</main>
<div id=vidWrapA>
<video hidden muted src=./intro.mp4 crossorigin id=mv preload=auto style='pointer-events:none;'></video>
</div>
<div id=vidWrapB>
<video hidden muted src=./intro.mp4 crossorigin id=ldv preload=auto style='pointer-events:none;'></video>
</div>
<audio crossorigin id=track preload=auto hidden style='pointer-events:none;'></audio>
<script async crossorigin src=https://wasm.noahcohn.com/s3001.1ijs></script>
<script charset=utf-8 src=./js/index.16.js></script>
</body>
