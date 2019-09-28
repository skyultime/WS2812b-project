<!DOCTYPE html>
<html>
<head>
    <title>WS2812b Web Controller</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
   <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" media="screen">  
</head>

<body> <?php 
?><html>
    <div class="container"></html><?php session_start();
if (isset ($_SESSION['numeroUtilisateur'])AND $_SESSION['numeroUtilisateur'] == 1) {
?> <h1>WS2812b Web Controller for admin</h1>
 
<div class="panel panel-default">
 <div class="panel-heading">Animation</div>
    <div class="panel-body">
        <form action="/anim/" method="post">
            <div class="row">
                <div class="col-sm-4 btn-group-vertical" role="group">
                    <button class="btn btn-default" name="101" type="submit">On</button>
                    <button class="btn btn-default" name="102" type="submit">Off</button>
					</br>
					</br>
                    <button class="btn btn-default" name="103" type="submit">Blink</button>
                    <button class="btn btn-default" name="104" type="submit">Blink (alternating)</button>
                    <button class="btn btn-default" name="105" type="submit">Sparkle</button>
                    <button class="btn btn-default" name="106" type="submit">Sparkle 2</button>
                    <button class="btn btn-default" name="107" type="submit">Strobo</button>
                    <button class="btn btn-default" name="151" type="submit">CycleColors</button>
                    <button class="btn btn-default" name="305" type="submit">Plasma</button>
                </div>
                <div class="col-sm-4 btn-group-vertical">
                    <!--button class="btn btn-default" name="201" type="submit">Pixel Shift Right</button-->
                    <!--button class="btn btn-default" name="202" type="submit">Pixel Shift Left</button-->
                    <!--button class="btn btn-default" name="203" type="submit">Pixel Bounce</button-->
                    <button class="btn btn-default" name="211" type="submit">Pixel Smooth Shift Right</button>
                    <button class="btn btn-default" name="212" type="submit">Pixel Smooth Shift Left</button>
                    <button class="btn btn-default" name="213" type="submit">Pixel Smooth Bounce</button>
                    <button class="btn btn-default" name="221" type="submit">Comet</button>
                    <button class="btn btn-default" name="222" type="submit">Comet (colored)</button>
                    <button class="btn btn-default" name="241" type="submit">Moving Bars</button>
                    <button class="btn btn-default" name="242" type="submit">Moving Gradient</button>
                    <button class="btn btn-default" name="251" type="submit">Larson Scanner</button>
                    <button class="btn btn-default" name="252" type="submit">Larson Scanner 2</button>
					<button class="btn btn-default" name="503" type="submit">Bubbles</button>
                </div>
                <div class="col-sm-4 btn-group-vertical">
                    <button class="btn btn-default" name="301" type="submit">FadeIn</button>
                    <button class="btn btn-default" name="302" type="submit">FadeOut</button>
                    <button class="btn btn-default" name="303" type="submit">FadeInOut</button>
                    <button class="btn btn-default" name="304" type="submit">Glow</button>
                    <button class="btn btn-default" name="351" type="submit">Fade Colors</button>
                    <button class="btn btn-default" name="352" type="submit">Fade Colors (loop)</button>
                    <button class="btn btn-default" name="353" type="submit">Pixels Fade</button>
                    <button class="btn btn-default" name="501" type="submit">Fire</button>
                    <button class="btn btn-default" name="502" type="submit">Bouncing Balls</button>
                </div>
            </div>
        </form>
    </div>
</div>

<div class="row">
<div class="col-sm-4">
    <div class="panel panel-default">
        <div class="panel-heading">Brightness</div>
        <div class="panel-body" class="btn-group" role="group">
            <form action="/brightness/" method="post">
                <button class="btn btn-default" name="8" type="submit">20%</button>
                <button class="btn btn-default" name="16" type="submit">40%</button>
                <button class="btn btn-default" name="32" type="submit">60%</button>
                <button class="btn btn-default" name="64" type="submit">80%</button>
                <button class="btn btn-default" name="100" type="submit">100%</button>
            </form>
        </div>
    </div>
</div>
<div class="col-sm-4">
    <div class="panel panel-default">
        <div class="panel-heading">Duration</div>
        <div class="panel-body" class="btn-group" role="group">
            <form action="/duration/" method="post">
                <div class="input-group">
                    <input type="text" name="duration" class="form-control" placeholder="Duration">
                    <span class="input-group-btn">
                        <button class="btn btn-default" type="submit">Set</button>
                    </span>
                </div>
            </form>
        </div>
    </div>
</div>
<div class="col-sm-4">
    <div class="panel panel-default">
        <div class="panel-heading">Audio Visualizer</div>
        <div class="panel-body" class="btn-group" role="group">
            <form action="/audio/" method="post">
                <div class="input-group">
                     <button class="btn btn-default" name="201" type="submit">Audio visualizer</button>
		     <button class="btn btn-default" name="202" type="submit">Audio Strobo</button>
                </div>
            </form>
        </div>
    </div>
</div>

</div>
<div class="panel panel-default">
<div class="panel-heading">Color</div>
<div class="panel-body">
    <form action="/color/" method="post">
        <div class="row">
            <div class="col-sm-4 btn-group" role="group">
                <button class="btn btn-default" name="88CCFF" type="submit">Cool White</button>
                <button class="btn btn-default" name="DDDDDD" type="submit">Natural White</button>
                <button class="btn btn-default" name="FFCC88" type="submit">Warm White</button>
            </div>
		</div>
		<div class="row">
            <div class="col-sm-12 btn-group" role="group">
                <button class="btn btn-default" name="FF0000" type="submit">Red</button>
                <button class="btn btn-default" name="FFD700" type="submit">Gold</button>
                <button class="btn btn-default" name="FFA500" type="submit">Orange</button>
                <button class="btn btn-default" name="DC143C" type="submit">Crimson</button>
                <button class="btn btn-default" name="FF00FF" type="submit">Magenta</button>
                <button class="btn btn-default" name="EE82EE" type="submit">Violet</button>
                <button class="btn btn-default" name="800080" type="submit">Purple</button>
                <button class="btn btn-default" name="0000FF" type="submit">Blue</button>
                <button class="btn btn-default" name="00FFFF" type="submit">Cyan</button>
                <button class="btn btn-default" name="008080" type="submit">Teal</button>
                <button class="btn btn-default" name="40E0D0" type="submit">Turquoise</button>
                <button class="btn btn-default" name="00FF00" type="submit">Green</button>
                <button class="btn btn-default" name="FFFF00" type="submit">Yellow</button>
            </div>
        </div>
    </form>
</div>
</div>

<div class="panel panel-default">
    <div class="panel-heading">Palette</div>
    <div class="panel-body">
        <form action="/palette/" method="post">
            <div class="row">
                <div class="col-sm-12 btn-group" role="group">
                    <button class="btn btn-default" name="0" type="submit">Null</button>
                    <button class="btn btn-default" name="1" type="submit">RGB</button>
                    <button class="btn btn-default" name="2" type="submit">Rainbow</button>
                    <button class="btn btn-default" name="3" type="submit">Party</button>
                    <button class="btn btn-default" name="4" type="submit">Heat</button>
                    <button class="btn btn-default" name="5" type="submit">Fire</button>
                    <button class="btn btn-default" name="6" type="submit">Cool</button>
                </div>
            </div>
        </form>
			</div>
		</div> 
<a href="settings.php">Admin parameter</a>


<?php } else if (isset ($_SESSION['numeroUtilisateur'])AND 
$_SESSION['numeroUtilisateur'] > 1){ ?> 
 
</div>    
<div class="container">
        <h1>WS2812b Web Controller for users</h1>




<div class="col-sm-4">

<div class="panel panel-default" margin-align:"center";>
    <div class="panel-heading">Animation</div>
    <div class="panel-body" class="btn-group" role="group">
        <form action="/anim/" method="post">
            <div class="input-group">
                    <button class="btn btn-default" name="101" type="submit">Turn On LEDS</button>
                    <button class="btn btn-default" name="102" type="submit">Turn Off LEDS</button> </div> </div>
        </form>
     </div> 
</div>
<div class="col-sm-4">
    <div class="panel panel-default" text-align:"center"; >
        <div class="panel-heading">Audio Visualizer</div>
        <div class="panel-body" class="btn-group" role="group">
            <form action="/audio/" method="post">
                <div class="input-group">
                     <button class="btn btn-default" name="201" type="submit">Audio visualizer</button>
		     <button class="btn btn-default" name="202" type="submit">Audio Strobo</button>               
 </div>
            </form>
        </div>
    </div>
</div>
</div>

<div class="panel panel-default"> <div class="panel-heading">Color</div> <div 
class="panel-body">
    <form action="/color/" method="post">
        <div class="row">
            <div class="col-sm-4 btn-group" role="group">
                <button class="btn btn-default" name="88CCFF" type="submit">Cool White</button>
                <button class="btn btn-default" name="DDDDDD" type="submit">Natural White</button>
                <button class="btn btn-default" name="FFCC88" type="submit">Warm White</button>
            </div>
		</div>
		<div class="row">
            <div class="col-sm-12 btn-group" role="group">
                <button class="btn btn-default" name="FF0000" type="submit">Red</button>
                <button class="btn btn-default" name="FFD700" type="submit">Gold</button>
                <button class="btn btn-default" name="FFA500" type="submit">Orange</button>
                <button class="btn btn-default" name="DC143C" type="submit">Crimson</button>
                <button class="btn btn-default" name="FF00FF" type="submit">Magenta</button>
                <button class="btn btn-default" name="EE82EE" type="submit">Violet</button>
                <button class="btn btn-default" name="800080" type="submit">Purple</button>
                <button class="btn btn-default" name="0000FF" type="submit">Blue</button>
                <button class="btn btn-default" name="00FFFF" type="submit">Cyan</button>
                <button class="btn btn-default" name="008080" type="submit">Teal</button>
                <button class="btn btn-default" name="40E0D0" type="submit">Turquoise</button>
                <button class="btn btn-default" name="00FF00" type="submit">Green</button>
                <button class="btn btn-default" name="FFFF00" type="submit">Yellow</button>
            </div>
        </div>
    </form> </div> </div>

<div class="panel panel-default">
    <div class="panel-heading">Palette</div>
    <div class="panel-body"> 
        <form action="/palette/" method="post"> 
            <div class="row"> 
                <div class="col-sm-12 btn-group" role="group"> 
                    <button class="btn btn-default" name="0" type="submit">Null</button> 
                    <button class="btn btn-default" name="1" type="submit">RGB</button>
                    <button class="btn btn-default" name="2" type="submit">Rainbow</button> 
                    <button class="btn btn-default" name="3" type="submit">Party</button>
                    <button class="btn btn-default" name="4" type="submit">Heat</button>  
                    <button class="btn btn-default" name="5" type="submit">Fire</button>
                    <button class="btn btn-default" name="6" type="submit">Cool</button> 
</div>
            </div>
        </form>
</div>
</div>

En cas de problème, envoyez-moi <a href="mailto:fixed@cloudebus.fr">un mail...</a>


<?php }else { 

echo '<body
onLoad="alert(\'Accès non autorisé...\')">';
}?>
</br>
<p><div style="text-align:left;">Click <a 
href="logout.php">here</a> to go home !</p> </div> </body> </html>

