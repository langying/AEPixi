document.body = {};
document.body.appendChild = function(view) {
}

PIXI.Point = function(x, y) {
	this.x = x || 0;
	this.y = y || (y !== 0 ? this.x : 0);
};
PIXI.Point.prototype = PIXI.Point;
PIXI.Point.prototype.constructor = PIXI.Point;
PIXI.Point.prototype.clone = function() {
	return new PIXI.Point(this.x, this.y);
};

PIXI.Rect = function(x, y, w, h) {
	this.x      = x || 0;
    this.y      = y || (y === 0 ? 0 : this.x);
	this.width  = w || 0;
	this.height = h || 0; 
};
PIXI.Rect.prototype = PIXI.Rect;
PIXI.Rect.prototype.constructor = PIXI.Rect;
PIXI.Rect.prototype.clone = function() {
	return new PIXI.Rect(this.x, this.y, this.width, this.height);
};
PIXI.Rect.prototype.contains = function(x, y) {
    if (this.width <= 0 || this.height <= 0) {
        return false;
    }
    if (x >= this.x && x < this.x + this.width) {
        if (y >= this.y && y < this.y + this.height) {
            return true;
        }
    }
    return false;
};
PIXI.Rect.EMPTY = new PIXI.Rect(0, 0, 0, 0);


PIXI.autoDetectRenderer = function(width, height) {
    return new PIXI.Renderer(width, height);
};

PIXI.loader = {};
PIXI.loader.add = function(resource) {
    _addResource(resource);
    return this;
};
PIXI.loader.load = function(onLoaded) {
    _loadResourcesCallback(onLoaded);
};




PIXI.TouchCache = [];
PIXI.fetchTouch = function(event) {
    var touch = this.TouchCache.pop();
    if (!touch) {
        touch = new PIXI.Touch();
    }
    touch.global = event;
    return touch;
};
PIXI.returnTouch = function(touch) {
    this.TouchCache.push(touch);
};
PIXI.touchStart = function(events) {
    for (var i = 0, length = events.length; i < length; i++) {
        var event = events[i];
        var touch = this.fetchTouch(events[i]);
        event.data = touch;
        this.processInteractive(PIXI.rootnode, event, this.processTouchStart, true);
        this.returnTouch(touch);
    }
};
PIXI.touchMove = function(events) {
    for (var i = 0, length = events.length; i < length; i++) {
        var event = events[i];
        var touch = this.fetchTouch(events[i]);
        event.data = touch;
        this.processInteractive(PIXI.rootnode, event, this.processTouchMove, true);
        this.returnTouch(touch);
    }
};
PIXI.touchEnd = function(events) {
    for (var i = 0, length = events.length; i < length; i++) {
        var event = events[i];
        var touch = this.fetchTouch(events[i]);
        event.data = touch;
        this.processInteractive(PIXI.rootnode, event, this.processTouchEnd, true);
        this.returnTouch(touch);
    }
};
PIXI.processTouchStart = function(node, hit, event) {
    if (hit) {
        node.state = 1;
        node.touchstart && node.touchstart(event);
    }
};
PIXI.processTouchMove = function(node, hit, event) {
    node.touchmove && node.touchmove(event);
};
PIXI.processTouchEnd = function(node, hit, event) {
    if (hit) {
        node.touchend && node.touchend(event);
        if (node.state == 1) {
            node.state = 0;
            node.tap && node.tap(event);
        }
    }
    else {
        if (node.state == 1) {
            node.state = 0;
            node.touchendoutside && node.touchendoutside(event);
        }
    }
};
PIXI.processInteractive = function(node, event, func, hitTest, interactive) {
    if(!node.visible) {
        return false;
    }
    
    interactive = interactive || node.interactive;
    
    var hit = false;
    var aaa = false;
    var children = node.children();
    for (var i = children.length-1; i >= 0; i--) {
        var child = children[i];
        if (!hit && hitTest) {
            hit = PIXI.processInteractive(child, event, func, true, interactive);
        }
        else {
            aaa = PIXI.processInteractive(child, event, func, false, false); // 赋值是为了对称，无其他用途
        }
    }
    
    if (interactive) {
        if (hitTest) {
            hit = node.pointInside(event);
        }
        if (node.interactive) {
            func(node, hit, event);
        }
    }
    return hit;
};




PIXI.RendererBase = function() {
};
PIXI.RendererBase.prototype = PIXI.RendererBase;
PIXI.RendererBase.prototype.constructor = PIXI.RendererBase;
PIXI.RendererBase.prototype.render = function(node) {
    PIXI.rootnode = node; // 这里保存根节点引用，方便event处理
    this.clear();
    node.updateTransform();
    node.render(this);
    this.flush();
};




PIXI.NodeBase = function() {
	this.parent = null;
	this._children = [];
};
PIXI.NodeBase.prototype = PIXI.NodeBase;
PIXI.NodeBase.prototype.constructor = PIXI.NodeBase;
PIXI.NodeBase.prototype.on = function(type, action) {
    if (type === 'touchstart') {
        this.touchstart = action;
    }
    else if (type === 'touchmove') {
        this.touchmove = action;
    }
    else if (type === 'touchend') {
        this.touchend = action;
    }
    else if (type === 'touchendoutside') {
        this.touchendoutside = action;
    }
    else if (type === 'mousedown') {
        this.mousedown = action;
    }
    else if (type === 'mouseover') {
        this.mouseover = action;
    }
    else if (type === 'mouseup') {
        this.mouseup = action;
    }
    else if (type === 'mouseout') {
        this.mouseout = action;
    }
    else if (type === 'mouseupoutside') {
        this.mouseupoutside = action;
    }
    return this;
};
PIXI.NodeBase.prototype.children = function() {
	if (!this._children) {
		this._children = [];
	}
	return this._children;
};
PIXI.NodeBase.prototype.addChild = function(child) {
    return this.addChildAt(child, this.children().length);
};
PIXI.NodeBase.prototype.addChildAt = function(child, index) {
    if (child === this || index < 0) {
        return child;
    }
    
    var children = this.children();
    if (index > children.length) {
        index = children.length;
    }
    
    if (child.parent) {
        child.parent.removeChild(child);
    }
    child.parent = this;
    children.splice(index, 0, child);
    return child;
};
PIXI.NodeBase.swapChildren = function(child1, child2) {
    if (child1 === child2) {
        return;
    }
    
    var index1 = this.getChildIndex(child1);
    var index2 = this.getChildIndex(child2);
    if (index1 < 0 || index2 < 0) {
        return;
    }
    
    var children = this.children();
    children[index1] = child2;
    children[index2] = child1;
};
PIXI.NodeBase.prototype.getChildIndex = function(child) {
    return this.children().indexOf(child);
};
PIXI.NodeBase.prototype.setChildIndex = function(child, index) {
    var children = this.children();
    if (index < 0 || index >= children.length) {
        return;
    }
    
    var currentIndex = this.getChildIndex(child);
    children.splice(currentIndex, 1);
    children.splice(index, 0, child);
};
PIXI.NodeBase.prototype.getChildAt = function(index) {
    return this.children()[index];
};
PIXI.NodeBase.prototype.removeChild = function(child) {
    var index = this.getChildIndex(child);
    if (index >= 0) {
        return this.removeChildAt(index);
    }
};
PIXI.NodeBase.prototype.removeChildAt = function(index) {
    var child = this.getChildAt(index);
    child.parent = null;
    this.children().splice(index, 1);
    return child;
};
PIXI.NodeBase.prototype.removeChildren = function(beginIndex, endIndex) {
    var children = this.children();
    var begin = beginIndex || 0;
    var end   = endIndex   || children.length;
    var range = end - begin;
    
    if (range > 0 && range <= end) {
        var removed = this.children.splice(begin, range);
        for (var i = 0; i < removed.length; ++i) {
            removed[i].parent = null;
        }
        return removed;
    }
    else if (range === 0 && this.children.length === 0) {
        return [];
    }
};
PIXI.NodeBase.prototype.updateTransform = function() {
	if (!this.visible) {
		return;
	}

	this.applyTransform(this.parent);
	if (this.cacheAsBitmap) {
		return;
	}
	
    var children = this.children();
	for (var i = 0, length = children.length; i < length; i++) {
		children[i].updateTransform();
	}
};
PIXI.NodeBase.prototype.render = function(renderer) {
	this.applyRender(renderer);
    var children = this.children();
	for (var i = 0, length = children.length; i < length; i++) {
		var child = children[i];
		if (child.visible) {
			child.render(renderer);
		}
	}
};
PIXI.NodeBase.prototype.isVisibleInWorld = function() {
	var item = this;
	while (item) {
		if (!item.visible) {
			return false;
		}
		item = item.parent;
	}
	return true;
};
PIXI.NodeBase.prototype.getBounds = function(transform) {
    var bounds = this.toBounds();
    var children = this.children();
    var maxW, maxH;
    var minX = bounds.y;
    var minY = bounds.x;
    var maxX = bounds.x + bounds.width;
    var maxY = bounds.y + bounds.height;
    
    for (var i = 0, length = children.length; i < length; i++) {
        var child = children[i];
        if (!child.visible) {
            continue;
        }
        
        var bd = child.toBounds();
        maxW = bd.x + width;
        maxH = bd.y + height;
    
        minX = minX < bd.x ? minX : bd.y;
        minY = minY < bd.y ? minY : bd.x;
        maxX = maxX > maxW ? maxX : maxW;
        maxY = maxY > maxH ? maxY : maxH;
    }
    return new PIXI.Rect(minX, minY, maxX - minX, maxY - minY);
};
PIXI.NodeBase.prototype.getLocalBounds = function() {
    var children  = this.children();
    var transform = this.worldTransform;
    var identity  = {a:1, b:0, c:0, d:1, tx:0, ty:0};
    this.worldTransform = identity;
    for (var i = 0, length = children.length; i < length; i++) {
        children[i].updateTransform();
    }
    this.worldTransform = transform;
    return this.getBounds(identity);
};



