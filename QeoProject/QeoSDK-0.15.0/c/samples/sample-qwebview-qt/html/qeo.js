/**
 * @license
 ************* COPYRIGHT AND CONFIDENTIALITY INFORMATION *********************
 **                                                                          **
 ** Copyright (c) 2012 Technicolor                                           **
 ** All Rights Reserved                                                      **
 **                                                                          **
 ** This program contains proprietary information which is a trade           **
 ** secret of TECHNICOLOR and/or its affiliates and also is protected as     **
 ** an unpublished work under applicable Copyright laws. Recipient is        **
 ** to retain this program in confidence and is not permitted to use or      **
 ** make copies thereof other than as permitted in a written agreement       **
 ** with TECHNICOLOR, UNLESS OTHERWISE EXPRESSLY ALLOWED BY APPLICABLE LAWS. **
 **                                                                          **
 ******************************************************************************/

//----------------------------------------------
// Provide dummy Native counterpart if missing
// (e.g. opened by a webbrower, native QeoJS will
//  be absent)
//----------------------------------------------
if (typeof QeoJS === "undefined") {
    /** @ignore */
    QeoJS = {
        /** @ignore */
        notify : function(event, data) {}
    }
}

//----------------------------------------------
// Qeo-library/module definition
//----------------------------------------------
/**
 * @global
 * @namespace
 * @classdesc Global object exposing the Qeo API
 * 
 */
Qeo = (function() {

/**
 * @license
 * The code from this point on, up to the SMOKESIGNALS-END marker, was taken 
 * from the smokesignals.js project. It is also separately available on
 * https://bitbucket.org/bentomas/smokesignals.js under the licensing terms
 * listed below:
 */
/**
 * @license
 * This code is free.  You can redistribute it and/or modify it in any
 * way that you see fit so long as if you redistribute it with any changes, you
 * don't call it the same thing.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */ 
smokesignals={convert:function(c,e){e={};c.on=function(d,a){(e[d]=e[d]||[]).push(a);return c};c.once=function(d,a){function b(){a.apply(c.off(d,b),arguments)}b.h=a;return c.on(d,b)};c.off=function(d,a){for(var b=e[d],f=0;a&&b&&b[f];f++)b[f]!=a&&b[f].h!=a||b.splice(f--,1);f||delete e[d];return c};c.emit=function(d){for(var a=e[d],b=0;a&&a[b];)a[b++].apply(c,a.slice.call(arguments,1));return c};return c}};

/** @license SMOKESIGNALS-END **/
/**
 * @license
 * The code from this point on, up to the PROMISE-END marker, was taken 
 * from the "then" project. It is also separately available on
 * https://github.com/then/promise under the licensing terms
 * listed below:
 */
/** 
 * @license
 * Copyright (c) 2013 Forbes Lindesay
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
(function(e){if("function"==typeof bootstrap)bootstrap("promise",e);else if("object"==typeof exports)module.exports=e();else if("function"==typeof define&&define.amd)define(e);else if("undefined"!=typeof ses){if(!ses.ok())return;ses.makePromise=e}else"undefined"!=typeof window?window.Promise=e():global.Promise=e()})(function(){var define,ses,bootstrap,module,exports;
return (function(e,t,n){function i(n,s){if(!t[n]){if(!e[n]){var o=typeof require=="function"&&require;if(!s&&o)return o(n,!0);if(r)return r(n,!0);throw new Error("Cannot find module '"+n+"'")}var u=t[n]={exports:{}};e[n][0].call(u.exports,function(t){var r=e[n][1][t];return i(r?r:t)},u,u.exports)}return t[n].exports}var r=typeof require=="function"&&require;for(var s=0;s<n.length;s++)i(n[s]);return i})({1:[function(require,module,exports){
// shim for using process in browser

var process = module.exports = {};

process.nextTick = (function () {
    var canSetImmediate = typeof window !== 'undefined'
    && window.setImmediate;
    var canPost = typeof window !== 'undefined'
    && window.postMessage && window.addEventListener
    ;

    if (canSetImmediate) {
        return function (f) { return window.setImmediate(f) };
    }

    if (canPost) {
        var queue = [];
        window.addEventListener('message', function (ev) {
            if (ev.source === window && ev.data === 'process-tick') {
                ev.stopPropagation();
                if (queue.length > 0) {
                    var fn = queue.shift();
                    fn();
                }
            }
        }, true);

        return function nextTick(fn) {
            queue.push(fn);
            window.postMessage('process-tick', '*');
        };
    }

    return function nextTick(fn) {
        setTimeout(fn, 0);
    };
})();

process.title = 'browser';
process.browser = true;
process.env = {};
process.argv = [];

process.binding = function (name) {
    throw new Error('process.binding is not supported');
}

// TODO(shtylman)
process.cwd = function () { return '/' };
process.chdir = function (dir) {
    throw new Error('process.chdir is not supported');
};

},{}],2:[function(require,module,exports){
'use strict'

var nextTick = require('./lib/next-tick')

module.exports = Promise
function Promise(fn) {
  if (!(this instanceof Promise)) return new Promise(fn)
  if (typeof fn !== 'function') throw new TypeError('not a function')
  var state = null
  var delegating = false
  var value = null
  var deferreds = []
  var self = this

  this.then = function(onFulfilled, onRejected) {
    return new Promise(function(resolve, reject) {
      handle(new Handler(onFulfilled, onRejected, resolve, reject))
    })
  }

  function handle(deferred) {
    if (state === null) {
      deferreds.push(deferred)
      return
    }
    nextTick(function() {
      var cb = state ? deferred.onFulfilled : deferred.onRejected
      if (cb === null) {
        (state ? deferred.resolve : deferred.reject)(value)
        return
      }
      var ret
      try {
        ret = cb(value)
      }
      catch (e) {
        deferred.reject(e)
        return
      }
      deferred.resolve(ret)
    })
  }

  function resolve(newValue) {
    if (delegating)
      return
    resolve_(newValue)
  }

  function resolve_(newValue) {
    if (state !== null)
      return
    try { //Promise Resolution Procedure: https://github.com/promises-aplus/promises-spec#the-promise-resolution-procedure
      if (newValue === self) throw new TypeError('A promise cannot be resolved with itself.')
      if (newValue && (typeof newValue === 'object' || typeof newValue === 'function')) {
        var then = newValue.then
        if (typeof then === 'function') {
          delegating = true
          then.call(newValue, resolve_, reject_)
          return
        }
      }
      state = true
      value = newValue
      finale()
    } catch (e) { reject_(e) }
  }

  function reject(newValue) {
    if (delegating)
      return
    reject_(newValue)
  }

  function reject_(newValue) {
    if (state !== null)
      return
    state = false
    value = newValue
    finale()
  }

  function finale() {
    for (var i = 0, len = deferreds.length; i < len; i++)
      handle(deferreds[i])
    deferreds = null
  }

  try { fn(resolve, reject) }
  catch(e) { reject(e) }
}


function Handler(onFulfilled, onRejected, resolve, reject){
  this.onFulfilled = typeof onFulfilled === 'function' ? onFulfilled : null
  this.onRejected = typeof onRejected === 'function' ? onRejected : null
  this.resolve = resolve
  this.reject = reject
}

},{"./lib/next-tick":4}],3:[function(require,module,exports){
'use strict'

//This file contains then/promise specific extensions to the core promise API

var Promise = require('./core.js')
var nextTick = require('./lib/next-tick')

module.exports = Promise

/* Static Functions */

Promise.from = function (value) {
  if (value instanceof Promise) return value
  return new Promise(function (resolve) { resolve(value) })
}
Promise.denodeify = function (fn) {
  return function () {
    var self = this
    var args = Array.prototype.slice.call(arguments)
    return new Promise(function (resolve, reject) {
      args.push(function (err, res) {
        if (err) reject(err)
        else resolve(res)
      })
      fn.apply(self, args)
    })
  }
}
Promise.nodeify = function (fn) {
  return function () {
    var args = Array.prototype.slice.call(arguments)
    var callback = typeof args[args.length - 1] === 'function' ? args.pop() : null
    try {
      return fn.apply(this, arguments).nodeify(callback)
    } catch (ex) {
      if (callback == null) {
        return new Promise(function (resolve, reject) { reject(ex) })
      } else {
        nextTick(function () {
          callback(ex)
        })
      }
    }
  }
}

Promise.all = function () {
  var args = Array.prototype.slice.call(arguments.length === 1 && Array.isArray(arguments[0]) ? arguments[0] : arguments)

  return new Promise(function (resolve, reject) {
    if (args.length === 0) return resolve([])
    var remaining = args.length
    function res(i, val) {
      try {
        if (val && (typeof val === 'object' || typeof val === 'function')) {
          var then = val.then
          if (typeof then === 'function') {
            then.call(val, function (val) { res(i, val) }, reject)
            return
          }
        }
        args[i] = val
        if (--remaining === 0) {
          resolve(args);
        }
      } catch (ex) {
        reject(ex)
      }
    }
    for (var i = 0; i < args.length; i++) {
      res(i, args[i])
    }
  })
}

/* Prototype Methods */

Promise.prototype.done = function (onFulfilled, onRejected) {
  var self = arguments.length ? this.then.apply(this, arguments) : this
  self.then(null, function (err) {
    nextTick(function () {
      throw err
    })
  })
}
Promise.prototype.nodeify = function (callback) {
  if (callback == null) return this

  this.then(function (value) {
    nextTick(function () {
      callback(null, value)
    })
  }, function (err) {
    nextTick(function () {
      callback(err)
    })
  })
}
},{"./core.js":2,"./lib/next-tick":4}],4:[function(require,module,exports){
(function(process){'use strict'

if (typeof setImmediate === 'function') { // IE >= 10 & node.js >= 0.10
  module.exports = function(fn){ setImmediate(fn) }
} else if (typeof process !== 'undefined' && process && typeof process.nextTick === 'function') { // node.js before 0.10
  module.exports = function(fn){ process.nextTick(fn) }
} else {
  module.exports = function(fn){ setTimeout(fn, 0) }
}

})(require("__browserify_process"))
},{"__browserify_process":1}]},{},[3])(3)
});
;

/** @license PROMISE-END **/


    // Define Qeo-library as being "strictly"
    "use strict";

    //----------------------------------------------
    // Module private variables
    //----------------------------------------------
    /** @private */
    var randomId = new Date().getTime(); // take UNIX timestamp as starting point
    /** @private */
    var BAD_ID   = -1;
    /** @private */
    var objects  = {};   // associative array: stores objects which can handle native notifications

    //----------------------------------------------
    // Factory management code
    // This should disappear over time, but for now
    // we must prevent two factories for the same 
    // realm being built at the same time because it
    // messes up the qeo-core layer.
    //----------------------------------------------
    /** @private */
    var factories = {
        CLOSED : 0,
        PENDING : 1,
        OPEN : 2,

        open : {
            state : 0,
            list : [],
            identity : null,
            manifest : null,
            backendFactory : null
        },
        closed : {
            state : 0,
            list : [],
            identity : null,
            manifest : null,
            backendFactory : null
        }
    };

    function isManifestCompatible(origmf, newmf) {
        /* manifests are compatible if
         *      - one of them is null, or
         *      - both are well-formed, and
         *              - newmf's permissions are a subset of origmf's permissions
         */
    	if (origmf === null) return true;
        if (newmf === null) return true;
        if (origmf.application === undefined) return false;
        if (newmf.application === undefined) return false;
        for (var topic in newmf.application) {
        	if (origmf.application[topic] === undefined) return false;
            origperm = origmf.application[topic];
            newperm = newmf.application[topic];
            if (origperm === "rw") continue;
            if (newperm !== origperm) return false;
        }
        return true;
    }
    function factoryGet(options) {
        if (options.identity === undefined) {
            options.identity = "default";
        }
        var isopen = options.identity === "open";
        return factoryGetSpecific(isopen ? factories.open : factories.closed, options);
    }
    function factoryGetSpecific(fac, options) {
        /* extract options.on -> we don't need to pass
         * that to the lower layers */
        var on = options.on;
        if (undefined !== on)
            delete options.on;
        else
            on = {};

        if (fac.state === factories.CLOSED) {
            return factoryCreate(fac, options, on);
        }

        if (options.identity !== fac.identity) {
            return new Promise(function(resolve, reject) {
                reject(new Error("Cannot currently create a factory for this secure domain. Close other secure factories first"));
            });
        }
        var manifest = (options.manifest === undefined ? null : options.manifest);
        if (!isManifestCompatible(fac.manifest, manifest)) {
            return new Promise(function(resolve, reject) {
                reject(new Error("You have already created a factory for this domain, and your current manifest is not a subset of that used in your previously created factory. This is currently unsupporeted. (See CRN DE2812)"));
            });
        }


        if (fac.state === factories.PENDING) {
            return new Promise(function(resolve, reject) {
                /* append this promise to the list of promises to be resolved
                 * or rejected when the factory is created */
                fac.list.push({resolve:resolve, reject:reject, on:on});
            });
        } else if (fac.state === factories.OPEN) {
            return new Promise(function(resolve, reject) {
               resolve(new Factory(fac.backendFactory, on));
            });
        }
    }
    function factoryCreate(fac, options, on) {
        fac.state = factories.PENDING;
        fac.list = [];
        fac.backendFactory = null;
        fac.identity = options.identity;
        fac.manifest = (options.manifest === undefined ? null : options.manifest);

        return newRequest("factory", "create", extend({},options), function(data) {
            if (data.id === undefined || data.id === -1) {
                throw new Error("Invalid factory id obtained");
            }
            return new BackendFactory(data.id);
        }).then(function(backendFactory) {
            fac.state = factories.OPEN;
            fac.backendFactory = backendFactory;

            /* make sure we have at least one reference to this backend factory
             * so that it cannot be closed while we're resolving the other pending
             * promises */
            var frontendFactory = new Factory(backendFactory, on);

            var to_resolve = fac.list;
            fac.list = [];

            for (var i = 0; i < to_resolve.length; ++i) {
                to_resolve[i].resolve(new Factory(backendFactory, to_resolve[i].on));
            }
            return frontendFactory;
        }, function(error) {
            fac.state = factories.CLOSED;
            fac.backendFactory = null;
            fac.identity  = null;
            var to_reject = fac.list;
            fac.list = [];
            for (var i = 0; i < to_reject.length; ++i) {
                to_reject[i].reject(error);
            }
            throw error;
        });
    }
    function factoryClose(backendFactory) {
        if (backendFactory === factories.open.backendFactory) {
            factoryCloseSpecific(factories.open);
        } else if (backendFactory === factories.closed.backendFactory) {
            factoryCloseSpecific(factories.closed);
        }
    }
    function factoryCloseSpecific(fac) {
        fac.state = factories.CLOSED;
        fac.backendFactory = null;
        fac.identity = null;
        fac.manifest = null;
        fac.list = [];
    }

    // Grab the Native Qeo object and keep a private reference to it
    // Remove the Native QeoJS object reference to prevent publically exposing its interfaces
    /** @private */
    var QeoNative = QeoJS;
    QeoJS = undefined;
    
    /* Some helper functions. */
    var slice = Function.prototype.call.bind(Array.prototype.slice);
    var identity = function(data) {return data;};
    
    var primitivetypes = {"boolean": true, "byte": true, "int16": true, "int32": true, "int64": true, "float": true, "string": true};
    var typeregistry = {types : {}};
    typeregistry.add = function(typedesc) {
        var entry = {};
        entry.typedesc = typedesc;
        entry.complete = true;
        for (var key in typedesc.properties) {
            var member = typedesc.properties[key];
            if (member.type === "object") {
                entry.complete = false;
            } else if (member.type === "array") {
                if (!(member.items.type in primitivetypes))
                    entry.complete = false;
            }
        }
        this.types[typedesc.topic] = entry;
    }
    typeregistry.lookup = function(typename) {
        if (typename in this.types)
            return this.types[typename].typedesc;
        return null;
    }
    typeregistry.iscomplete = function(typename) {
        if (typename in this.types)
            return this.types[typename].complete;
        return false;
    }
    typeregistry.complete_type = function(typename) {
        var entry = this.types[typename];
        if (entry === undefined) return false;
        if (entry.complete) return true;
        var td = entry.typedesc;
        for (var key in td.properties) {
            var member = td.properties[key];
            if (member.type === "object") {
                if ((typeof member.item) === "string") {
                    var completed = this.complete_type(member.item);
                    if (completed) {
                        // substitute type name with completed type
                        member.item = this.lookup(member.item);
                    } else {
                        // cannot complete type, abort
                        return false;
                    }
                }
            } else if (member.type === "array") {
                if (member.items.type === "object") {
                    if ((typeof member.items.item) === "string") {
                        var completed = this.complete_type(member.items.item);
                        if (completed) {
                            // substitute type name with completed type
                            member.items.item = this.lookup(member.items.item);
                        } else {
                            // cannot complete type, abort
                            return false;
                        }
                    }
                }
            }
        }
        entry.complete = true;
        return true;
    }
    
    // catch types that were defined by generated code included before qeo.js
    if (typeof Qeo !== "undefined" && Qeo.ttr !== undefined) {
        for (var i = 0; i < Qeo.ttr.length; ++i) {
            typeregistry.add(Qeo.ttr[i]);
        }
    }

    
    /* Extend a object with properties of all other arguments. */
    function extend(obj) {
        if(obj) {
            var extenders = slice(arguments, 1);
            for(var i = 0, length = extenders.length; i < length; ++i) {
                var extender = extenders[i];
                for(var prop in extender) {
                    obj[prop] = extender[prop];
                }
            }
        }
        return obj;
    }

    /**
     * @private
     * @description Group public API's together for easy export.
     */
    var publicAPIs = {}; // groups all Qeo API's which we exposed to the public

    /**
     * @ignore
     * @description Called by generated code for registering types in the type registry
     */
    publicAPIs.registerType = function(typedesc) {
        typeregistry.add(typedesc);
    }

    /**
     * @ignore
     * @description Callback for native webkit bridged notifications: "delegated"-events.
     * @exports publicAPIs.notify as Qeo.notify
     * @function
     * @param {string} id Object identifier to be notified
     * @param {string} event Event to be send to the object
     * @param {string} jsonData Data describing parameters in JSON format
     */
    publicAPIs.notify = function(id, event, jsonData) {
        // Check if object is available
        if (objects[id] === undefined) return;

        // Decode the json string
        var data = JSON.parse(jsonData);
        // Forward native notification (smokesignal) to the found object
        objects[id].emit(event, data);
    }

    /**
     * @description Closes all Factories and associated Qeo objects.
     * @memberof Qeo
     * @name cleanup
     */
    publicAPIs.cleanup = function () {
        // Run through all the objects and find the factories
        for (var key in objects) {
            if (objects[key].ident.objType === "factory") {
                // Factory found => send close notification
                objects[key].close();
            }
        }
        // Cleaup the entire list of objects
        objects = {};
    }
    
    /**
     * Construct a Backend object.
     * @private 
     * @constructor
     */
    function BackendObject(objType, id, parentId, extra_ident) {
        var me = this;
        me.id = id;
        smokesignals.convert(me);
        objects[id] = me;

        me.ident = extend({
            id : id,
            objType: objType
        }, extra_ident);

        /*Register this object as child of the parent.*/
        if(parentId !== undefined) {
            var parent = objects[parentId];
            (parent.c = parent.c || []).push(me)
        }

        /**
         * Send an event on the backend object.
         * @param event name of the vent
         * @param data data to send to backend.  This object becomes invalid.
         * @private 
         **/
        me.notify = function (event, data) {
            var msg = data ? extend(data, me.ident) : me.ident;
            QeoNative.notify(event, JSON.stringify(msg));
        };

        /**
         * unregister the object from the backend objects
         * @private 
         **/
        me.unregister = function() {
            if(parentId !== undefined) {
                var parent = objects[parentId], list = parent.c, i = 0;

                for(; list && list[i]; ++i) {
                    if(list[i] === me) {
                        list.splice(--i, 1);
                    }
                }

                if(0 == i) {
                    //no children registered at parent anymore.
                    delete parent.c;
                }
            }

            if(me.c) {
                var children = me.c;
                // Prevent our children list to be manipulated by the child unregister.
                delete me.c;
                children.forEach(function(child){child.unregister();});
            }

            // Make sure that nothing can be send to the backend anymore.
            // So we replace it by a stub.
            me.notify = identity;
            delete objects[id];
        };
    }
    
    /**
     * Create a new request, for which we want to receive a response.
     * @param objType the object type to create a request for
     * @param event the event sent to the backend
     * @param data extra fields to be send to the backend
     * @param sync_cb Callback to be called synchronously. [optional]
     *                Promisses cannot be used as we are forced to do some things synchronously.
     * @param on_event the event and the event to wait for do not alwyas line up.
     *                 So override it here.
     * @return a promise which will give you the response or response manipulated by the sync_cb.
     */
    function newRequest (objType, event, data, sync_cb, on_event) {
        var request = new BackendObject(objType, "req_"+ randomId++);
        on_event = on_event || event;
        sync_cb = sync_cb || identity;
        
        // Create a promise
        var promise = new Promise(function(resolve, reject) {
            // Request: Attach event handler for event
            request.once(on_event, function() {
                try {
                    resolve(sync_cb.apply(this, arguments));
                } catch(e) {
                    reject(e);
                }
                
                request.unregister();
            });
            // Request: Attach event handler for event: "error"
            request.once("error", function(data) {
                reject(new Error(data.error || ("Failed to perform " + event)));
                request.unregister();
            });
        });

        // Send request
        request.notify(event, data);
        return promise;
    }

    //----------------------------------------------
    // Helper Function: to create a promise
    //----------------------------------------------
    function _createReaderOrWriter(factoryId, ctor, typeName, options) {
        return new Promise(function(resolve, reject) {
            // check if we have a complete type description.
            // If not, we reject outright
            var complete = typeregistry.complete_type(typeName);
            if (!complete) {
                reject(new Error("Type " + typeName + " is not complete"));
                return;
            }

            var typeDesc = typeregistry.lookup(typeName);
            var type = ctor.t;
            var msg = extend({
                factoryId : factoryId,
                typeDesc : typeDesc,
                objType : type
            }, options);
            var on = msg.on;
            if(undefined !== on) {
                delete msg.on;
            }

            resolve(newRequest(type, "create", msg, function(data) {
                if (data.id === undefined || data.id === -1)
                    throw new Error("Invalid Qeo object id obtained");
                else {
                    return new ctor(data.id, factoryId, on);
                }
            }));

        });
    }

    /**
     * @name createFactory
     * @memberof Qeo
     * @public
     * @method
     * @description Creates a Factory object, which provides you access to the Qeo Realm.
     * @param {Object} [options] Object describing additional optional parameters to be
     *                       used during factory creation (e.g. <code>{"manifest":{}, "identity":{}}</code>).<br>
     *                       The identity parameter allows you to choose the Realm to which the factory
     *                       is attached:
     *                       <ul>
     *                       <li><code>"identity":"open"</code> creates a factory for the public open domain
     *                       <li><code>"identity":"default"</code>, or omitting the identity field entirely,
     *                       creates a factory for your secure Realm.
     *                       <li>any other value will currently result in an error
     *                       </ul><br>
     *                       A factory can also emit event by registering them in an <code>on</code> container:
     *                       <ul>
     *                       <li>{@link Factory#event:termination|termination}</li>
     *                       </ul>
     * @return {Promise} A promise object, which will be resolved into an object of type {@link Factory}
     */
    publicAPIs.createFactory = function(options) {
        return factoryGet(options);
    };


    //----------------------------------------------
    // JSDoc only: add additional documentation for:
    // - Promise library
    // - Smokesignal extentions for Qeo objects
    // - Add class descriptions for Qeo objects that
    //   have a private constructor
    //----------------------------------------------

    /**
     * @name Promise
     * @class
     * @description Represents the result of a task, which may or may not have been completed.<br>
     *              A promise can only take one state at any given time: <b>unfulfilled</b>, <b>fulfilled</b> or <b>failed</b>.<br>
     *              The constructor of a Promise is private.
     */
    /**
     * @name then
     * @function Promise.prototype.then
     * @description Adds a fulfilledHandler and an errorHandler to be called for completion of a promise.<br>
     *              Both arguments are optional and non-function values are ignored. <br>
     *              They will always be called asynchronously<br>
     *              Returns a new Promise that is fulfilled when the given handler callback is finished.
     *              This allows promise operations to be chained together. <br>
     *              The value returned from the callback handler is the fulfillment value for the returned promise.
     *              If the callback throws an error, the returned promise will be moved to failed state.
     * @param {function} [onFulfilled] Called when the promise is fulfilled
     * @param {function} [onRejected]  Called when a promise fails
     */
    /**
     * @name done
     * @function  Promise.prototype.done
     * @description Adds a fulfilledHandler and an errorHandler to be called for completion of a promise.<br>
     *              Both arguments are optional and non-function values are ignored. They will always be called asynchronously<br>
     *              It does not return a promise and is thereby not chainable. Any exceptions that occur are re-thrown.
     * @param {function} [onFulfilled] Called when the promise is fulfilled
     * @param {function} [onRejected]  Called when a promise fails
     */

    /**
     * @name Factory
     * @class
     * @classdesc A Qeo Factory encapsulates your application's connection to a given Qeo Realm.
     *              This class allows you to create Qeo readers and Qeo writers.
     * @description This constructor is private. Use {@link Qeo.createFactory} to create a Factory object.
     */

    /**
     * @name EventWriter
     * @class
     * @description An EventWriter is used to publish events on a Topic.<br>
     *              The constructor of an EventWriter is private. Use {@link Factory#createEventWriter|Factory.createEventWriter} to create event writers.
     * @borrows StateChangeReader#event:error as EventWriter#error
     * @borrows StateChangeReader#event:policyUpdate as EventWriter#policyUpdate
     */
    /**
     * @name on
     * @function EventWriter#on
     * @description Add a listener for an event.
     *              An EventWriter emits
     *              <ul>
     *              <li>{@link EventWriter#error|error}
     *              <li>{@link EventWriter#policyUpdate|policyUpdate}
     *              </ul>
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * @name off
     * @function EventWriter#off
     * @description Remove a listener for an event.
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */

    /**
     * @name StateWriter
     * @class
     * @description A StateWriter is used to publish state information on a Topic.<br>
     *              The constructor of a StateWriter is private. Use {@link Factory#createStateWriter|Factory.createStateWriter} to create state writers.
     * @borrows StateChangeReader#event:error as StateWriter#error
     * @borrows StateChangeReader#event:policyUpdate as StateWriter#policyUpdate
     */
    /**
     * @name on
     * @function StateWriter#on
     * @description Add a listener for an event.
     *              A StateWriter emits
     *              <ul>
     *              <li>{@link StateWriter#error|error}
     *              <li>{@link StateWriter#policyUpdate|policyUpdate}
     *              </ul>
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * @name off
     * @function StateWriter#off
     * @description Remove a listener for an event.
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */

    /**
     * @name EventReader
     * @class
     * @description An EventReader is used for subscribing to event topics.<br>
     *              The constructor of an EventReader is private. Use {@link Factory#createEventReader|Factory.createEventReader} to create event readers.
     * @borrows StateChangeReader#event:data as EventReader#data
     * @borrows StateChangeReader#event:noMoreData as EventReader#noMoreData
     * @borrows StateChangeReader#event:error as EventReader#error
     * @borrows StateChangeReader#event:policyUpdate as EventReader#policyUpdate
     */
    /**
     * @name on
     * @function EventReader#on
     * @description Add a listener for an event.
     *              An EventReader emits
     *              <ul>
     *              <li>{@link EventReader#data|data}
     *              <li>{@link EventReader#noMoreData|noMoreData}
     *              <li>{@link EventReader#error|error}
     *              <li>{@link EventReader#policyUpdate|policyUpdate}
     *              </ul>
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * @name off
     * @function EventReader#off
     * @description Remove a listener for an event.
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */

    /**
     * @name StateReader
     * @class
     * @description An StateReader is used for subscribing to state topics.
     *              It creates a local cache that holds the latest state for all instances on the topic.<br>
     *              The constructor of a StateReader is private. Use {@link Factory#createStateReader|Factory.createStateReader} to create state readers.
     * @borrows StateChangeReader#event:policyUpdate as StateReader#policyUpdate
     * @borrows StateChangeReader#event:error as StateReader#error
     */
    /**
     * @name on
     * @function  StateReader#on
     * @description Add a listener for an event.
     *              A StateReader emits
     *              <ul>
     *              <li>{@link StateReader#event:update|update}
     *              <li>{@link StateReader#error|error}
     *              <li>{@link StateReader#policyUpdate|policyUpdate}
     *              </ul>
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * @name off
     * @function  StateReader#off
     * @description Remove a listener for an event.
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * This event is triggered whenever something changes (an instance is added, updated or removed) on the reader's topic.
     * The associated handler is invoked without arguments.
     *
     * @event StateReader#update
     */


    /**
     * @name StateChangeReader
     * @class
     * @description A StateChangeReader is used for subscribing to state topics. <br>
     *              There is no cache maintained for the latest states on instances of a topic. <br>
     *              It offers state changes in the form of events. Several state transitions maybe aggregated into one event.<br>
     * The constructor of a StateChangeReader is private. Use {@link Factory#createStateChangeReader|Factory.createStateChangeReader} to create state change readers.
     */
    /**
     * @name on
     * @function  StateChangeReader#on
     * @description Add a listener for an event.
     *              A StateChangeReader emits
     *              <ul>
     *              <li>{@link StateChangeReader#event:data|data}
     *              <li>{@link StateChangeReader#event:remove|remove}
     *              <li>{@link StateChangeReader#event:noMoreData|noMoreData}
     *              <li>{@link StateChangeReader#event:error|error}
     *              <li>{@link StateChangeReader#event:policyUpdate|policyUpdate}
     *              </ul>
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */
    /**
     * @name off
     * @function  StateChangeReader#off
     * @description Remove a listener for an event.
     * @param {string} eventName Name of the event
     * @param {function} handler Handler associated with the event
     */

    /**
     * This event is triggered whenever new data is available on the reader.
     * The data is passed as an object to the handler.
     *
     * @event StateChangeReader#data
     */
    
    /**
     * This event is triggered whenever an instance is removed from the reader's topic.
     * The instance being removed is passed as argument to the handler. Note: only the <em>key</em>
     * fields of the instance have valid values; all the other fields should be ignored.
     *
     * @event StateChangeReader#remove
     */
    
    /**
     * This event is triggered after each burst of <em>data</em> and <em>remove</em> events triggered on
     * the reader. It indicates that there are no immediate pending events left
     * for this reader. The associated handler is called without arguments.
     *
     * @event StateChangeReader#noMoreData
     */

    /**
     * This event is triggered whenever an error occurs.
     * 
     * @event StateChangeReader#error
     * @type Object
     * @property {string} error The error message
     */

    /**
     * This event is triggered whenever the policy for this entity's topic has changed.
     * 
     * @event StateChangeReader#policyUpdate
     * @type ApplicationDefinedPolicy
     */
    
    /**
     * This event is triggered when a factory is terminated abnormally.
     * (eg on android if the qeo service is killed).
     * After receiving this event all readers/writer associated with this factory
     * and the factory itself are closed and cannot be used anymore.
     *
     * @event Factory#termination
     */

    /**
     * @typedef UserTopicPermission
     * @type Object
     * @description An individual Realm User's permission to read or write on a
     *              topic. This data structure is used in the policyUpdate events triggered
     *              by readers or writers. For a writer, this represents the user's permission
     *              to read what this writer publishes. For a reader, this represents whether
     *              the reader wants to receive publications by this writer.
     * @property {number} id The user ID
     * @property {boolean} allow true if the user is allowed to send information to the reader or receive information from the writer.
     */

    /**
     * @typedef ApplicationDefinedPolicy
     * @type Object
     * @description An application-defined policy for a specific reader or writer.
     *              This data structure is used throughout the whole 
     *              {@link EventWriter#policyUpdate|policyUpdate}/{@link EventWriter#updatePolicy|updatePolicy} mechanism for all readers and writers.
     * @property {Array<UserTopicPermission>} users List of users and their permissions with respect to this reader or writer.
     */

    /**
     * @typedef DeviceId
     * @type Object
     * @description This type represents your device in Qeo space as a 128-bit UUID
     * @property {string} upper Higher 64-bit part of the UUID.
     * @property {string} lower Lower 64-bit part of the UUID.
     */

    //----------------------------------------------
    // Mixins
    //----------------------------------------------
    
    /**
     * Mixin for Qeo entities
     */
    function MixinQeoEntity(bo) {
        /**
         * @description Closes and cleans up all objects related to the factory.
         */
        this.close = bo.close = function() {
            bo.notify("close");
            bo.unregister();
        };
    }
    
    /**
     * Mixin for Qeo Readers or Writers.
     */
    function MixinQeoReaderOrWriter(objType, id, factoryId, on) {
        var bo = new BackendObject(objType, id, factoryId, {factoryId: factoryId});
        var me = this;
        
        MixinQeoEntity.call(me, bo);
        
        me.updatePolicy = function(policy) {
            if (undefined === policy) policy = {"users": []};
            bo.notify("policyUpdate",{data:policy});
        };
        
        me.requestPolicy = function() {
            bo.notify("requestPolicy");
        };

        /** We expose all events here, should we do this?*/
        me.on = function(eventName, handler) {
            function wrappedHandler() {
                handler.apply(me, arguments);
            }
            //Make sure off() will work with original handler.
            wrappedHandler.h = handler;

            bo.on(eventName, wrappedHandler);
            return me;
        };

        me.off = function(eventName, handler) {
            bo.off(eventName, handler);
            return me;
        };

        
        if (undefined !== on) {
            // Loop through all the eventhandlers and add them
            for (var property in on) {
                // Register event handler
                me.on(property,on[property]);
            }
        }

        return bo;
    }
    
    function MixinQeoWriter(objType, id, factoryId, on) {
        var bo = MixinQeoReaderOrWriter.call(this, objType, id, factoryId, on);
        
        this.write = function(data) {
            bo.notify("write",{data:data});
        };
        
        return bo;
    }
    
    var MixinQeoReader = MixinQeoReaderOrWriter;

    //----------------------------------------------
    // Constructors
    //----------------------------------------------

    /**
     * @description Creates an instance of Factory.
     * @private
     * @constructor
     * @param {BackendFactory} backendFactory Internal object that tracks the underlying factory on the backend
     */
    function Factory(backendFactory, on) {
        smokesignals.convert(this);
        backendFactory.incref(this);

        /* install initial event handlers */
        if (undefined !== on) {
            for (var key in on) {
                this.on(key, on[key]);
            }
        }

        /**
         * @description Closes and cleans up all objects related to the factory.
         * @public
         * @function Factory#close
         */
        this.close = function() {
            backendFactory.decref(this);
        };
        
        /**
         * @description Get the Qeo DeviceId structure.
         * @function Factory#getDeviceId
         * @return {Promise} A promise object, which will be resolved into an object of type {@link DeviceId}.                           
         */
        this.getDeviceId = function() {
            return backendFactory.getDeviceId();
        };
        
        /**
         * @description Creates an event writer for the given type description.
         * @function Factory#createEventWriter
         * @param {string} typeName Fully-qualified type name for the writer's topic (e.g. "org::qeo::sample::Foo")
         * @param {Object} [options] Object containing additional optional parameters:
	 * <ul>
	 * <li><code>enablePolicy</code>: To activate "policyUpdate" events, default is false.
	 *     e.g. <code>{"enablePolicy":true}</code>
	 * <li><code>on</code>: object containing handlers for the events that can be emitted by the created writer.
	 *     Handlers that are passed in this way are guaranteed to be called for all events that are emitted by the writer.
	 *     If you wait until the promise is resolved, and add your handlers via the <code>on()</code> method on the writer,
	 *     you may miss some events that were emitted between the time the writer is created and the promise is resolved.
	 *     The following events can be emitted by this writer:
	 *     <ul>
	 *     <li>{@link EventWriter#error|error}
	 *     <li>{@link EventWriter#policyUpdate|policyUpdate}
	 *     </ul>
	 * </ul>
         * @return {Promise} A promise object, which will be resolved into an object of type {@link EventWriter}.
         */
        this.createEventWriter = function(typeName, options) {
            return backendFactory.createEventWriter(typeName, options);
        };
        
        /**
         * @description Creates an event reader for the given type description.
         * @function Factory#createEventReader
         * @param {string} typeName Fully-qualified type name for the reader's topic (e.g. "org::qeo::sample::Foo")
         * @param {Object} [options] Object containing additional optional parameters:
	 * <ul>
	 * <li><code>enablePolicy</code>: To activate "policyUpdate" events, default is false.
	 *     e.g. <code>{"enablePolicy":true}</code>
	 * <li><code>on</code>: object containing handlers for the events that can be emitted by the created reader.
	 *     Handlers that are passed in this way are guaranteed to be called for all events that are emitted by the reader.
	 *     If you wait until the promise is resolved, and add your handlers via the <code>on()</code> method on the reader,
	 *     you may miss some events that were emitted between the time the reader is created and the promise is resolved.
	 *     The following events can be emitted by this reader:
	 *     <ul>
	 *     <li>{@link EventReader#data|data}
	 *     <li>{@link EventReader#noMoreData|noMoreData}
	 *     <li>{@link EventReader#error|error}
	 *     <li>{@link EventReader#policyUpdate|policyUpdate}
	 *     </ul>
	 * </ul>
         * @return {Promise} A promise object, which will be resolved into an object of type {@link EventReader}.
         */
        this.createEventReader = function(typeName, options) {
            return backendFactory.createEventReader(typeName, options);
        };

        /**
         * @description Creates an state writer for the given type description.
         * @function Factory#createStateWriter
         * @param {string} typeName Fully-qualified type name for the writer's topic (e.g. "org::qeo::sample::Foo")
         * @param {Object} [options] Object containing additional optional parameters:
	 * <ul>
	 * <li><code>enablePolicy</code>: To activate "policyUpdate" events, default is false.
	 *     e.g. <code>{"enablePolicy":true}</code>
	 * <li><code>on</code>: object containing handlers for the events that can be emitted by the created writer.
	 *     Handlers that are passed in this way are guaranteed to be called for all events that are emitted by the writer.
	 *     If you wait until the promise is resolved, and add your handlers via the <code>on()</code> method on the writer,
	 *     you may miss some events that were emitted between the time the writer is created and the promise is resolved.
	 *     The following events can be emitted by this writer:
	 *     <ul>
	 *     <li>{@link StateWriter#error|error}
	 *     <li>{@link StateWriter#policyUpdate|policyUpdate}
	 *     </ul>
	 * </ul>
         * @return {Promise} A promise object, which will be resolved into an object of type {@link StateWriter}.
         */
        this.createStateWriter = function(typeName, options) {
            return backendFactory.createStateWriter(typeName, options);
        };
        
        /**
         * @description Creates an state reader for the given type description.
         * @function Factory#createStateReader
         * @param {string} typeName Fully-qualified type name for the reader's topic (e.g. "org::qeo::sample::Foo")
         * @param {Object} [options] Object containing additional optional parameters:
	 * <ul>
	 * <li><code>enablePolicy</code>: To activate "policyUpdate" events, default is false.
	 *     e.g. <code>{"enablePolicy":true}</code>
	 * <li><code>on</code>: object containing handlers for the events that can be emitted by the created reader.
	 *     Handlers that are passed in this way are guaranteed to be called for all events that are emitted by the reader.
	 *     If you wait until the promise is resolved, and add your handlers via the <code>on()</code> method on the reader,
	 *     you may miss some events that were emitted between the time the reader is created and the promise is resolved.
	 *     The following events can be emitted by this reader:
	 *     <ul>
	 *     <li>{@link StateReader#event:update|update}
	 *     <li>{@link StateReader#error|error}
	 *     <li>{@link StateReader#policyUpdate|policyUpdate}
	 *     </ul>
	 * </ul>
         * @return {Promise} A promise object, which will be resolved into an object of type {@link StateReader}.
         */
        this.createStateReader = function(typeName, options) {
            return backendFactory.createStateReader(typeName, options);
        };
        
        /**
         * @description Creates an state change reader for the given type description.
         * @function Factory#createStateChangeReader
         * @param {string} typeName Fully-qualified type name for the reader's topic (e.g. "org::qeo::sample::Foo")
         * @param {Object} [options] Object containing additional optional parameters:
	 * <ul>
	 * <li><code>enablePolicy</code>: To activate "policyUpdate" events, default is false.
	 *     e.g. <code>{"enablePolicy":true}</code>
	 * <li><code>on</code>: object containing handlers for the events that can be emitted by the created reader.
	 *     Handlers that are passed in this way are guaranteed to be called for all events that are emitted by the reader.
	 *     If you wait until the promise is resolved, and add your handlers via the <code>on()</code> method on the reader,
	 *     you may miss some events that were emitted between the time the reader is created and the promise is resolved.
	 *     The following events can be emitted by this reader:
	 *     <ul>
	 *     <li>{@link StateChangeReader#event:data|data}
	 *     <li>{@link StateChangeReader#event:remove|remove}
	 *     <li>{@link StateChangeReader#event:noMoreData|noMoreData}
	 *     <li>{@link StateChangeReader#event:error|error}
	 *     <li>{@link StateChangeReader#event:policyUpdate|policyUpdate}
	 *     </ul>
	 * </ul>
         * @return {Promise} A promise object, which will be resolved into an object of type {@link StateChangeReader}.
         */
        this.createStateChangeReader = function(typeName, options) {
            return backendFactory.createStateChangeReader(typeName, options);
        };
    }

    /** @private */
    function BackendFactory(id) {
        var bo = new BackendObject("factory", id);
        var self = this;

        /* keep track of the frontend Factory objects that sit 
         * in front of this BackendFactory. If we get a termination
	     * event from below, we need to be able to pass it on */
        this.frontends = [];

        this.incref = function(frontend) {
		this.frontends.push(frontend);
        }

        this.decref = function(frontend) {
	    var index = this.frontends.indexOf(frontend);
	    if (index != -1) {
	    	this.frontends.splice(index, 1);
	    }
            if (this.frontends.length === 0) {
                factoryClose(this);
                this.close();
            }
        }

        /* handle unfriendly termination from below (i.e. the Qeo Service died on Android) */
        bo.on("termination", function() {
            factoryClose(self);
            for (var i = 0; i < self.frontends.length; ++i) {
                self.frontends[i].emit("termination");
            }
        });
        
        /** @private */
        MixinQeoEntity.call(this, bo);
        
        /** @private */
        this.getDeviceId = function() {
            return newRequest("deviceId", "get", bo.ident, null, "data");
        };
        
        /** @private */
        this.createEventWriter = function(typeName, options) {
            return _createReaderOrWriter(id, EventWriter, typeName, options);
        };
        
	/** @private */
        this.createEventReader = function(typeName, options) {
            return _createReaderOrWriter(id, EventReader, typeName, options);
        };
        
	/** @private */
        this.createStateWriter = function(typeName, options) {
            return _createReaderOrWriter(id, StateWriter, typeName, options);
        };
        
	/** @private */
        this.createStateReader = function(typeName, options) {
            return _createReaderOrWriter(id, StateReader,typeName, options);
        };
        
	/** @private */
        this.createStateChangeReader = function(typeName, options) {
            return _createReaderOrWriter(id, StateChangeReader, typeName, options);
        };
    }

    /**
     * @description Creates an instance of EventWriter.
     * @private
     * @constructor
     * @param {string} id Unique identifier for the EventWriter object
     * @param {string} factoryId Identifier of the factory where it belongs too
     */
    function EventWriter(id, factoryId, on) {
        
        /**
         * @description Closes and cleans up the event writer object.
         * @function EventWriter#close
         */

        /**
         * @description Update EventWriter policy with the provided permission. The resulting policy information after modification
         *              will be returned asynchronously via the <code>policyUpdate</code> event.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
	 *
         * @function EventWriter#updatePolicy
         * @param {ApplicationDefinedPolicy} policy Fine grained policy information to be applied to this EventWriter.
         */

        /**
         * @description Request EventWriter policy information. The policy data is returned asynchronously via the <code>policyUpdate</code> event.
         * @function EventWriter#requestPolicy
         */

        /**
         * @description Write data to the topic.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
         * @function EventWriter#write
         * @param {Object} data Object containing the data to be written.
         */
        var bo = MixinQeoWriter.call(this, EventWriter.t, id, factoryId, on);
    }
    EventWriter.t = "eventWriter";

    /**
     * @description Creates an instance of StateWriter.
     * @private
     * @constructor
     * @param {string} id Unique identifier for the StateWriter object
     * @param {string} factoryId Identifier of the factory where it belogs too
     */
    function StateWriter(id, factoryId, on) {
        
        /**
         * @description Closes and cleans up the state writer object.
         * @function StateWriter#close
         */

        /**
         * @description Update StateWriter policy with the provided permission. The resulting policy information after modification
         *              will be returned asynchronously via the <code>policyUpdate</code> event.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
	 *
         * @function StateWriter#updatePolicy
         * @param {ApplicationDefinedPolicy} policy Fine grained policy information to be applied to this StateWriter.
         */

        /**
         * @description Request StateWriter policy information. The policy data is returned asynchronously via the <code>policyUpdate</code> event.
         * @function StateWriter#requestPolicy
         */

        /**
         * @description Write data to the topic.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
         * @function StateWriter#write
         * @param {Object} data Object containing the data to be written.
         */

        var bo = MixinQeoWriter.call(this, StateWriter.t, id, factoryId, on);
        
        /**
         * @description Remove an instance from the topic.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
         * @function StateWriter#remove
	 * @param {Object} data Object describing the instance to be
	 *                      removed. Note: you need to provide a "full" object here (all fields
	 *                      need to be present), even though only the values in the key fields
	 *                      are relevant.
         */
        this.remove = function(data) {
            bo.notify("remove",{data:data});
        }
    }
    StateWriter.t = "stateWriter";

    /**
     * @description Creates an instance of EventReader.
     * @private
     * @constructor
     * @param {string} id Unique identifier for the EventReader object
     * @param {string} factoryId Identifier of the factory where it belogs too
     */
    function EventReader(id, factoryId, on) {
        /**
         * @description Closes and cleans up the event reader object.
         * @function EventReader#close
         */

        /**
         * @description Update EventReader policy with the provided permission. The resulting policy information after modification
         *              will be returned asynchronously via the <code>policyUpdate</code> event.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
	 *
         * @function EventReader#updatePolicy
         * @param {ApplicationDefinedPolicy} policy Fine grained policy information to be applied to this EventReader.
         */

        /**
         * @description Request EventReader policy information. The policy data is returned asynchronously via the <code>policyUpdate</code> event.
         * @function EventReader#requestPolicy
         */

        var bo = MixinQeoReader.call(this, EventReader.t, id, factoryId, on);
    }
    EventReader.t = "eventReader";

    /**
     * @description Creates an instance of StateReader.
     * @private
     * @constructor
     * @param {string} id Unique identifier for the StateReader object
     * @param {string} factoryId Identifier of the factory where it belogs too
     */
    function StateReader(id, factoryId, on) {
        /**
         * @description Closes and cleans up the state reader object.
         * @function StateReader#close
         */

        /**
         * @description Update StateReader policy with the provided permission. The resulting policy information after modification
         *              will be returned asynchronously via the <code>policyUpdate</code> event.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
	 *
         * @function StateReader#updatePolicy
         * @param {ApplicationDefinedPolicy} policy Fine grained policy information to be applied to this StateReader.
         */

        /**
         * @description Request StateReader policy information. The policy data is returned asynchronously via the <code>policyUpdate</code> event.
         * @function StateReader#requestPolicy
         */

        var bo = MixinQeoReader.call(this, StateReader.t, id, factoryId, on);

        /**
         * @description Iterate over the instances on the reader's topic.<br>
         * There are 3 ways to use the iterator:
         * <ol>
	 * <li>
         *    <code>obj.iterate(function(arg) { per-instance processing }).then(function(){},function(error){}); </code><br>
         *        You can handle the instances as they come in.
	 * <li>
         *    <code>obj.iterate(function(arg) { return one or more fields per instance }).then(function(elements){}, function(error){});</code><br>
         *        In case your function returns values/objects, the complete collection will be returned
         *              as an array when the promise is resolved.
	 * <li>
         *    <code>obj.iterate().then(function(elements){},function(error){});</code><br>
         *        In this case the promise will be resolved with an array containing all instances on the topic.
         * </ol>
         *
         * @function StateReader#iterate
         * @param {function} [fn = function(x){return&nbsp;x;}] iterator function that will be called for each instance on the topic.
	 *                        If this function returns a value, these values will be accumulated in an array,
	 *                        which will then be used to resolve the promise that is returned by the iterate() call.
	 *                        If no iterator function is provided, the identity function is used. As a result, the promise will be
	 *                        resolved with an array containing all instances on the topic.
         * @throws {TypeError} An error is thrown when a non function argument is provided.
	 * @return {Promise} A promise that will be resolved with an array consisting of the return values of all executed iterator callbacks.
         */
        this.iterate = function(fn) {
            fn = fn || identity;
            
            if (typeof fn !== 'function') throw new TypeError('The provided iterator callback is not a function');
            
            var readerId = id;
            // create a request
            return newRequest("iterator", "create", {factoryId: factoryId, readerId:readerId}, function(data) {
                if (data.id === undefined || data.id === -1) {
                   throw new Error("Invalid iterator id obtained");
                }
                
                return new Promise(function(resolve, reject) {
                    // Create the iterator object (puts it self into the objects list)
                    var itr = new BackendObject("iterator", data.id, readerId);
                    var collection = [];

                    // Iterator: Attach event handler for event: "iterate"
                    itr.on("iterate",function(data) {
                        var y = fn(data);
                        if (undefined !== y) {
                            // The provided function returns a value/obj:
                            // Put this into the collection
                            collection.push(y);
                        }
                    });
                    // Iterator: Attach event handler for event: "close"
                    itr.once("close",function(data) {
                        itr.unregister();
                        // Resolve the promise with the collection
                        resolve(collection);
                    });
                    // Iterator: Attach event handler for event: "error"
                    itr.once("error",function(data) {
                        reject(new Error(data.error || "Error encountered during iteration"));
                    });
                });
            });
        };
    }
    StateReader.t = "stateReader";

    /**
     * @description Creates an instance of StateChangeReader.
     * @private
     * @constructor
     * @param {string} id Unique identifier for the StateChangeReader object
     * @param {string} factoryId Identifier of the factory where it belogs too
     */
    function StateChangeReader(id, factoryId, on) {
        /**
         * @description Closes and cleans up the state change reader object.
         * @function StateChangeReader#close
         */

        /**
         * @description Update StateChangeReader policy with the provided permission. The resulting policy information after modification
         *              will be returned asynchronously via the <code>policyUpdate</code> event.<br>
         *              If something goes wrong, an <code>error</code> event is emitted.
	 *
         * @function StateChangeReader#updatePolicy
         * @param {ApplicationDefinedPolicy} policy Fine grained policy information to be applied to this StateChangeReader.
         */

        /**
         * @description Request StateChangeReader policy information. The policy data is returned asynchronously via the <code>policyUpdate</code> event.
         * @function StateChangeReader#requestPolicy
         */
        var bo = MixinQeoReader.call(this, StateChangeReader.t, id, factoryId, on);
    }
    StateChangeReader.t = "stateChangeReader";


    //----------------------------------------------
    // expose public API's
    //----------------------------------------------
    return publicAPIs;
})();
