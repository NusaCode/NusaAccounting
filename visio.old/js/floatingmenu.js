document.observe('click', function(event) {
// console.log('haha');
if (! (event.target.id=="contextMenu" || event.target.tagName == 'IMG') ){$('contextMenu').style.display = "none";}

if (event.target.tagName == 'IMG' && event.target.id.substring(0,3)=="img") {
var ypos=event.target.positionedOffset().top+event.target.getHeight();
var xpos=event.target.positionedOffset().left;

$('contextMenu').style.top = ypos +"px";
$('contextMenu').style.left = xpos + "px";
$('contextMenu').innerHTML=event.target.nextSibling.innerHTML;

if($('contextMenu').style.display == "none"){
$('contextMenu').style.display = "block";
}else
{
$('contextMenu').style.display = "none";
}

  }

});