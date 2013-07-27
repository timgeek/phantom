// Adapted from https://github.com/ariya/phantomjs/blob/master/examples/loadspeed.js
var page = require('webpage').create(),
    system = require('system'),
    t, address;

t = Date.now();
address = system.args[1];
page.open(address, function (status) {
	t = Date.now() - t;
	console.log('Page title is ' + page.evaluate(function () {
		return document.title;
	}));
	console.log('Loading time ' + t + ' msec');
	phantom.exit();
});
