(auto i 0)

(while (< i 100)
  (prog 
    (cond ((and (not (% i 3)) (not (% i 5))) (print "FizzBuzz"))
          ((not (% i 3)) (print "Fizz"))
          ((not (% i 5)) (print "Buzz"))
          (print i))
    (set i (+ i 1))))
