# ceceo
a toy lisp like language

```lisp
(auto i 0)

(while (< i 30)
  (prog 
    (cond ((&& (! (% i 3)) (! (% i 5))) (print "FizzBuzz"))
          ((! (% i 3)) (print "Fizz"))
          ((! (% i 5)) (print "Buzz"))
          (print i))
    (set i (+ i 1))))
```
