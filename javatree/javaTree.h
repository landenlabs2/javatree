//
//
// Author: Dennis Lang - 2015
// http://landenlabs.com
//
// This file is part of JavaTree project.
//
// ----- License ----
//
// Copyright (c) 2015 Dennis Lang
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

const char version[] = "v1.4";

const char nofile[] = "_no_file_";
const char interface[] = "interface";

const char dtree_css[] = 
	".dtree {\n"
	"	font-family: Verdana, Geneva, Arial, Helvetica, sans-serif;\n"
	"	font-size: 11px;\n"
	"	color: #666;\n"
	"	white-space: nowrap;\n"
	"}\n"
	".dtree img {\n"
	"	border: 0px;\n"
	"	vertical-align: middle;\n"
	"}\n"
	".dtree a {\n"
	"	color: #333;\n"
	"	text-decoration: none;\n"
	"}\n"
	".dtree a.node, .dtree a.nodeSel {\n"
	"	white-space: nowrap;\n"
	"	padding: 1px 2px 1px 2px;\n"
	"}\n"
	".dtree a.node:hover, .dtree a.nodeSel:hover {\n"
	"	color: #333;\n"
	"	text-decoration: underline;\n"
	"}\n"
	".dtree a.nodeSel {\n"
	"	background-color: #c0d2ec;\n"
	"}\n"
	".dtree .clip {\n"
	"	overflow: hidden;\n"
	"}\n";

const char dtree_js[] = 
"/*--------------------------------------------------|\n"
"| dTree 2.05 | www.destroydrop.com/javascript/tree/ |\n"
"|---------------------------------------------------|\n"
"| Copyright (c) 2002-2003 Geir Landr                |\n"
"|                                                   |\n"
"| This script can be used freely as long as all     |\n"
"| copyright messages are intact.                    |\n"
"|                                                   |\n"
"| Updated: 17.04.2003                               |\n"
"|--------------------------------------------------*/\n"
"\n"
"// Node object\n"
"function Node(id, pid, name, url, title, target, icon, iconOpen, open) {\n"
"	this.id = id;\n"
"	this.pid = pid;\n"
"	this.name = name;\n"
"	this.url = url;\n"
"	this.title = title;\n"
"	this.target = target;\n"
"	this.icon = icon;\n"
"	this.iconOpen = iconOpen;\n"
"	this._io = open || false;\n"
"	this._is = false;\n"
"	this._ls = false;\n"
"	this._hc = false;\n"
"	this._ai = 0;\n"
"	this._p;\n"
"};\n"
"\n"
"// Tree object\n"
"function dTree(objName) {\n"
"	this.config = {\n"
"		target		: null,\n"
"		folderLinks	: true,\n"
"		useSelection	: true,\n"
"		useCookies	: true,\n"
"		useLines	: true,\n"
"		useIcons	: true,\n"
"		useStatusText	: false,\n"
"		closeSameLevel	: false,\n"
"		inOrder		: false\n"
"	}\n"
"	this.icon = {\n"
"		root		: 'img/base.gif',\n"
"		folder		: 'img/folder.gif',\n"
"		folderOpen	: 'img/folderopen.gif',\n"
"		node		: 'img/page.gif',\n"
"		empty		: 'img/empty.gif',\n"
"		line		: 'img/line.gif',\n"
"		join		: 'img/join.gif',\n"
"		joinBottom	: 'img/joinbottom.gif',\n"
"		plus		: 'img/plus.gif',\n"
"		plusBottom	: 'img/plusbottom.gif',\n"
"		minus		: 'img/minus.gif',\n"
"		minusBottom	: 'img/minusbottom.gif',\n"
"		nlPlus		: 'img/nolines_plus.gif',\n"
"		nlMinus		: 'img/nolines_minus.gif'\n"
"	};\n"
"	this.obj = objName;\n"
"	this.aNodes = [];\n"
"	this.aIndent = [];\n"
"	this.root = new Node(-1);\n"
"	this.selectedNode = null;\n"
"	this.selectedFound = false;\n"
"	this.completed = false;\n"
"};\n"
"\n"
"// Adds a new node to the node array\n"
"dTree.prototype.add = function(id, pid, name, url, title, target, icon, iconOpen, open) {\n"
"	this.aNodes[this.aNodes.length] = new Node(id, pid, name, url, title, target, icon, iconOpen, open);\n"
"};\n"
"\n"
"// Open/close all nodes\n"
"dTree.prototype.openAll = function() {\n"
"	this.oAll(true);\n"
"};\n"
"dTree.prototype.closeAll = function() {\n"
"	this.oAll(false);\n"
"};\n"
"\n"
"// Outputs the tree to the page\n"
"dTree.prototype.toString = function() {\n"
"	var str = '<div class=\"dtree\">\\n';\n"
"	if (document.getElementById) {\n"
"		if (this.config.useCookies) this.selectedNode = this.getSelected();\n"
"		str += this.addNode(this.root);\n"
"	} else str += 'Browser not supported.';\n"
"	str += '</div>';\n"
"	if (!this.selectedFound) this.selectedNode = null;\n"
"	this.completed = true;\n"
"	return str;\n"
"};\n"
"\n"
"// Creates the tree structure\n"
"dTree.prototype.addNode = function(pNode) {\n"
"	var str = '';\n"
"	var n=0;\n"
"	if (this.config.inOrder) n = pNode._ai;\n"
"	for (n; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n].pid == pNode.id) {\n"
"			var cn = this.aNodes[n];\n"
"			cn._p = pNode;\n"
"			cn._ai = n;\n"
"			this.setCS(cn);\n"
"			if (!cn.target && this.config.target) cn.target = this.config.target;\n"
"			if (cn._hc && !cn._io && this.config.useCookies) cn._io = this.isOpen(cn.id);\n"
"			if (!this.config.folderLinks && cn._hc) cn.url = null;\n"
"			if (this.config.useSelection && cn.id == this.selectedNode && !this.selectedFound) {\n"
"					cn._is = true;\n"
"					this.selectedNode = n;\n"
"					this.selectedFound = true;\n"
"			}\n"
"			str += this.node(cn, n);\n"
"			if (cn._ls) break;\n"
"		}\n"
"	}\n"
"	return str;\n"
"};\n"
"\n"
"// Creates the node icon, url and text\n"
"dTree.prototype.node = function(node, nodeId) {\n"
"	var str = '<div class=\"dTreeNode\">' + this.indent(node, nodeId);\n"
"	if (this.config.useIcons) {\n"
"		if (!node.icon) node.icon = (this.root.id == node.pid) ? this.icon.root : ((node._hc) ? this.icon.folder : this.icon.node);\n"
"		if (!node.iconOpen) node.iconOpen = (node._hc) ? this.icon.folderOpen : this.icon.node;\n"
"		if (this.root.id == node.pid) {\n"
"			node.icon = this.icon.root;\n"
"			node.iconOpen = this.icon.root;\n"
"		}\n"
"		str += '<img id=\"i' + this.obj + nodeId + '\" src=\"' + ((node._io) ? node.iconOpen : node.icon) + '\" alt=\"\" />';\n"
"	}\n"
"	if (node.url) {\n"
"		str += '<a id=\"s' + this.obj + nodeId + '\" class=\"' + ((this.config.useSelection) ? ((node._is ? 'nodeSel' : 'node')) : 'node') + '\" href=\"' + node.url + '\"';\n"
"		if (node.title) str += ' title=\"' + node.title + '\"';\n"
"		if (node.target) str += ' target=\"' + node.target + '\"';\n"
"		if (this.config.useStatusText) str += ' onmouseover=\"window.status=\\'' + node.name + '\\';return true;\" onmouseout=\"window.status=\\'\\';return true;\" ';\n"
"		if (this.config.useSelection && ((node._hc && this.config.folderLinks) || !node._hc))\n"
"			str += ' onclick=\"javascript: ' + this.obj + '.s(' + nodeId + ');\"';\n"
"		str += '>';\n"
"	}\n"
"	else if ((!this.config.folderLinks || !node.url) && node._hc && node.pid != this.root.id)\n"
"		str += '<a href=\"javascript: ' + this.obj + '.o(' + nodeId + ');\" class=\"node\">';\n"
"	str += node.name;\n"
"	if (node.url || ((!this.config.folderLinks || !node.url) && node._hc)) str += '</a>';\n"
"	str += '</div>';\n"
"	if (node._hc) {\n"
"		str += '<div id=\"d' + this.obj + nodeId + '\" class=\"clip\" style=\"display:' + ((this.root.id == node.pid || node._io) ? 'block' : 'none') + ';\">';\n"
"		str += this.addNode(node);\n"
"		str += '</div>';\n"
"	}\n"
"	this.aIndent.pop();\n"
"	return str;\n"
"};\n"
"\n"
"// Adds the empty and line icons\n"
"dTree.prototype.indent = function(node, nodeId) {\n"
"	var str = '';\n"
"	if (this.root.id != node.pid) {\n"
"		for (var n=0; n<this.aIndent.length; n++)\n"
"			str += '<img src=\"' + ( (this.aIndent[n] == 1 && this.config.useLines) ? this.icon.line : this.icon.empty ) + '\" alt=\"\" />';\n"
"		(node._ls) ? this.aIndent.push(0) : this.aIndent.push(1);\n"
"		if (node._hc) {\n"
"			str += '<a href=\"javascript: ' + this.obj + '.o(' + nodeId + ');\"><img id=\"j' + this.obj + nodeId + '\" src=\"';\n"
"			if (!this.config.useLines) str += (node._io) ? this.icon.nlMinus : this.icon.nlPlus;\n"
"			else str += ( (node._io) ? ((node._ls && this.config.useLines) ? this.icon.minusBottom : this.icon.minus) : ((node._ls && this.config.useLines) ? this.icon.plusBottom : this.icon.plus ) );\n"
"			str += '\" alt=\"\" /></a>';\n"
"		} else str += '<img src=\"' + ( (this.config.useLines) ? ((node._ls) ? this.icon.joinBottom : this.icon.join ) : this.icon.empty) + '\" alt=\"\" />';\n"
"	}\n"
"	return str;\n"
"};\n"
"\n"
"// Checks if a node has any children and if it is the last sibling\n"
"dTree.prototype.setCS = function(node) {\n"
"	var lastId;\n"
"	for (var n=0; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n].pid == node.id) node._hc = true;\n"
"		if (this.aNodes[n].pid == node.pid) lastId = this.aNodes[n].id;\n"
"	}\n"
"	if (lastId==node.id) node._ls = true;\n"
"};\n"
"\n"
"// Returns the selected node\n"
"dTree.prototype.getSelected = function() {\n"
"	var sn = this.getCookie('cs' + this.obj);\n"
"	return (sn) ? sn : null;\n"
"};\n"
"\n"
"// Highlights the selected node\n"
"dTree.prototype.s = function(id) {\n"
"	if (!this.config.useSelection) return;\n"
"	var cn = this.aNodes[id];\n"
"	if (cn._hc && !this.config.folderLinks) return;\n"
"	if (this.selectedNode != id) {\n"
"		if (this.selectedNode || this.selectedNode==0) {\n"
"			eOld = document.getElementById(\"s\" + this.obj + this.selectedNode);\n"
"			eOld.className = \"node\";\n"
"		}\n"
"		eNew = document.getElementById(\"s\" + this.obj + id);\n"
"		eNew.className = \"nodeSel\";\n"
"		this.selectedNode = id;\n"
"		if (this.config.useCookies) this.setCookie('cs' + this.obj, cn.id);\n"
"	}\n"
"};\n"
"\n"
"// Toggle Open or close\n"
"dTree.prototype.o = function(id) {\n"
"	var cn = this.aNodes[id];\n"
"	this.nodeStatus(!cn._io, id, cn._ls);\n"
"	cn._io = !cn._io;\n"
"	if (this.config.closeSameLevel) this.closeLevel(cn);\n"
"	if (this.config.useCookies) this.updateCookie();\n"
"};\n"
"\n"
"// Open or close all nodes\n"
"dTree.prototype.oAll = function(status) {\n"
"	for (var n=0; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n]._hc && this.aNodes[n].pid != this.root.id) {\n"
"			this.nodeStatus(status, n, this.aNodes[n]._ls)\n"
"			this.aNodes[n]._io = status;\n"
"		}\n"
"	}\n"
"	if (this.config.useCookies) this.updateCookie();\n"
"};\n"
"\n"
"// Opens the tree to a specific node\n"
"dTree.prototype.openTo = function(nId, bSelect, bFirst) {\n"
"	if (!bFirst) {\n"
"		for (var n=0; n<this.aNodes.length; n++) {\n"
"			if (this.aNodes[n].id == nId) {\n"
"				nId=n;\n"
"				break;\n"
"			}\n"
"		}\n"
"	}\n"
"	var cn=this.aNodes[nId];\n"
"	if (cn.pid==this.root.id || !cn._p) return;\n"
"	cn._io = true;\n"
"	cn._is = bSelect;\n"
"	if (this.completed && cn._hc) this.nodeStatus(true, cn._ai, cn._ls);\n"
"	if (this.completed && bSelect) this.s(cn._ai);\n"
"	else if (bSelect) this._sn=cn._ai;\n"
"	this.openTo(cn._p._ai, false, true);\n"
"};\n"
"\n"
"// Closes all nodes on the same level as certain node\n"
"dTree.prototype.closeLevel = function(node) {\n"
"	for (var n=0; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n].pid == node.pid && this.aNodes[n].id != node.id && this.aNodes[n]._hc) {\n"
"			this.nodeStatus(false, n, this.aNodes[n]._ls);\n"
"			this.aNodes[n]._io = false;\n"
"			this.closeAllChildren(this.aNodes[n]);\n"
"		}\n"
"	}\n"
"}\n"
"\n"
"// Closes all children of a node\n"
"dTree.prototype.closeAllChildren = function(node) {\n"
"	for (var n=0; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n].pid == node.id && this.aNodes[n]._hc) {\n"
"			if (this.aNodes[n]._io) this.nodeStatus(false, n, this.aNodes[n]._ls);\n"
"			this.aNodes[n]._io = false;\n"
"			this.closeAllChildren(this.aNodes[n]);		\n"
"		}\n"
"	}\n"
"}\n"
"\n"
"// Change the status of a node(open or closed)\n"
"dTree.prototype.nodeStatus = function(status, id, bottom) {\n"
"	eDiv	= document.getElementById('d' + this.obj + id);\n"
"	eJoin	= document.getElementById('j' + this.obj + id);\n"
"	if (this.config.useIcons) {\n"
"		eIcon	= document.getElementById('i' + this.obj + id);\n"
"		eIcon.src = (status) ? this.aNodes[id].iconOpen : this.aNodes[id].icon;\n"
"	}\n"
"	eJoin.src = (this.config.useLines)?\n"
"	((status)?((bottom)?this.icon.minusBottom:this.icon.minus):((bottom)?this.icon.plusBottom:this.icon.plus)):\n"
"	((status)?this.icon.nlMinus:this.icon.nlPlus);\n"
"	eDiv.style.display = (status) ? 'block': 'none';\n"
"};\n"
"\n"
"\n"
"// [Cookie] Clears a cookie\n"
"dTree.prototype.clearCookie = function() {\n"
"	var now = new Date();\n"
"	var yesterday = new Date(now.getTime() - 1000 * 60 * 60 * 24);\n"
"	this.setCookie('co'+this.obj, 'cookieValue', yesterday);\n"
"	this.setCookie('cs'+this.obj, 'cookieValue', yesterday);\n"
"};\n"
"\n"
"// [Cookie] Sets value in a cookie\n"
"dTree.prototype.setCookie = function(cookieName, cookieValue, expires, path, domain, secure) {\n"
"	document.cookie =\n"
"		escape(cookieName) + '=' + escape(cookieValue)\n"
"		+ (expires ? '; expires=' + expires.toGMTString() : '')\n"
"		+ (path ? '; path=' + path : '')\n"
"		+ (domain ? '; domain=' + domain : '')\n"
"		+ (secure ? '; secure' : '');\n"
"};\n"
"\n"
"// [Cookie] Gets a value from a cookie\n"
"dTree.prototype.getCookie = function(cookieName) {\n"
"	var cookieValue = '';\n"
"	var posName = document.cookie.indexOf(escape(cookieName) + '=');\n"
"	if (posName != -1) {\n"
"		var posValue = posName + (escape(cookieName) + '=').length;\n"
"		var endPos = document.cookie.indexOf(';', posValue);\n"
"		if (endPos != -1) cookieValue = unescape(document.cookie.substring(posValue, endPos));\n"
"		else cookieValue = unescape(document.cookie.substring(posValue));\n"
"	}\n"
"	return (cookieValue);\n"
"};\n"
"\n"
"// [Cookie] Returns ids of open nodes as a string\n"
"dTree.prototype.updateCookie = function() {\n"
"	var str = '';\n"
"	for (var n=0; n<this.aNodes.length; n++) {\n"
"		if (this.aNodes[n]._io && this.aNodes[n].pid != this.root.id) {\n"
"			if (str) str += '.';\n"
"			str += this.aNodes[n].id;\n"
"		}\n"
"	}\n"
"	this.setCookie('co' + this.obj, str);\n"
"};\n"
"\n"
"// [Cookie] Checks if a node id is in a cookie\n"
"dTree.prototype.isOpen = function(id) {\n"
"	var aOpen = this.getCookie('co' + this.obj).split('.');\n"
"	for (var n=0; n<aOpen.length; n++)\n"
"		if (aOpen[n] == id) return true;\n"
"	return false;\n"
"};\n"
"\n"
"// If Push and pop is not implemented by the browser\n"
"if (!Array.prototype.push) {\n"
"	Array.prototype.push = function array_push() {\n"
"		for(var i=0;i<arguments.length;i++)\n"
"			this[this.length]=arguments[i];\n"
"		return this.length;\n"
"	}\n"
"};\n"
"if (!Array.prototype.pop) {\n"
"	Array.prototype.pop = function array_pop() {\n"
"		lastElement = this[this.length-1];\n"
"		this.length = Math.max(this.length-1,0);\n"
"		return lastElement;\n"
"	}\n"
"};\n";

