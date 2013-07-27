var page = require('webpage').create();
var system = require('system');
var address, height, width, output

// Get the input parameters.
address = system.args[1];
output = system.args[2];
height = system.args[3];
width = system.args[4];
console.log(address);

if (system.args[3].substr(-4) === ".pdf") {
  page.paperSize = { width: width, height: height, margin: '0px' };
}

page.open(address, function (status) {
	page.viewportSize = { width: width, height: height };
	page.render(output);
	phantom.exit();
});
