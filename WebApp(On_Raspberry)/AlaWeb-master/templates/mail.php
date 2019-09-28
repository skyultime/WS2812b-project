<!DOCTYPE html>
<html>
<body>

<h2>JavaScript Prompt</h2>

<button onclick="myFunction()">Try it</button>

<p id="demo"></p>

<script>
function myFunction() {
  var txt;
  var person = prompt("Entrez votre adresse e-mail afin que nous vous envoyons un login et un mot de passe invité", "");
  if (person == null || person == "") {
    txt = "User cancelled the prompt.";
  } else {
     //send e-mail
      
  }
  document.getElementById("demo").innerHTML = txt;
}
</script>

</body>
</html>

