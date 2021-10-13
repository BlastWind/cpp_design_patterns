function AddCommand(x) {
  let addBy = x;
  return {
    execute: (y) => {
      return y + addBy;
    },
    undo: (z) => z - addBy,
  };
}

const ohyea = AddCommand(10);
const newVal = ohyea.execute(3);
console.log(ohyea.undo(newVal));
