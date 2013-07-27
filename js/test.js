var page = require('webpage').create();
var system = require('system');
var address, height, width, output

address = system.args[1];
selector = system.args[2];
jqueryurl = system.args[3];

console.log(address);
console.log(selector);

page.onConsoleMessage = function(msg) {
	console.log(msg);
};

page.open(address, function(status) {
	page.includeJs(jqueryurl, function() {
		page.evaluate(function(selector) {
			$.each($(selector), function(index, value) {
  			console.log(index + ': ' + $(this).text() + ': ' + value);
			});
		}, selector);
	phantom.exit();
	});
});
