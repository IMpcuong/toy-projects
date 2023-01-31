let grownMap = new Map();

// NOTE: Deprecated in some browsers.
grownMap.__defineGetter__("keys", function() {
  return Object.keys(grownMap);
});
// NOTE: Deprecated in some browsers.
grownMap.__defineGetter__("values", function() {
  let ret = [];
  grownMap.forEach((e) => {
    ret.push(e.value);
  });
  return ret;
});

Object.defineProperty(grownMap, "firstElement", {
  get() {
    return grownMap.length > 0 && grownMap.has(0)
      ? grownMap.get(0)
      : new Object();
  },
  configurable: true,
  enumerable: true,
});

const values = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
let indices = new Uint8Array(values);
let iterable = (function* () {
  yield* values;
})();

if (indices.length <= 10) {
  indices = new Uint8Array(iterable);
  console.log(indices);
}

// NOTE: `null` objects declaration methods:
const obj1 = Object.create(null);
const obj2 = { __proto__: null };
const obj3 = new Object();
console.log(obj1, obj2, obj3);

// NOTE: Reassure the object is an instance of array type.
// if (!Array.isArray(values)) return;

const AdvancedHuman = class extends Object {
  static name = "IMpcuong";

  // NOTE: A class may only have one constructor.
  constructor(_name, _age) {
    super(_name, _age);
    this.name = _name;
    this.age = _age;
  }

  // Getters:
  get description() {
    return this.genDesc();
  }

  // Setters:
  /**
   * @param {String} _name
   */
  set setName(_name) {
    this.name = `My name is ${_name}`;
  }

  /**
   * @param {Number} _age
   */
  set setAge(_age) {
    this.age = `With current age: ${_age}`;
  }

  // Methods:
  genDesc() {
    return this.name + this.age;
  }

  *getFields() {
    yield this.name;
    yield this.age;
  }
}

indices.forEach((i) => {
  const impc = new AdvancedHuman(AdvancedHuman.name, i);
  grownMap.set(i, AdvancedHuman.create(impc));
});
console.log(grownMap);
for (const [k, v] of grownMap) {
  const destructure = [...v.getFields()];
  console.log(`${k} = ${destructure}`);
}

grownMap.forEach((e) => console.log("Avant-gardist:", typeof e, e instanceof AdvancedHuman));
console.log(grownMap.firstElement);
console.log(grownMap.keys);
console.log(grownMap.values);

function singletonConversion(object) {
  let singleton = object.__proto__;
  if (singleton.__singleton__) return null;

  singleton = Object.create(null);
  Object.defineProperty(singleton, {
    __singleton__: { values: true },
  });
  singleton.__proto__ = object.__proto__;
  object.__proto__ = singleton;

  return singleton;
}