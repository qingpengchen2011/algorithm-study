(define (merge-sort a)
    (define (merge left right)
        (cond ((null? left) right)
	      ((null? right) left)
              ((<= (car left) (car right))
		  (cons (car left) (merge (cdr left) right)))
	      (else
		  (cons (car right) (merge left (cdr right))))))

    (define (left-n a n)
        (if (= n 0)
	    '()
            (cons (car a) (left-n (cdr a) (- n 1)))))
    (define (skip-n a n)
	(if (= n 0)
	    a
            (skip-n (cdr a) (- n 1))))
    (cond ((= (length a) 0) '())
 	  ((= (length a) 1) a)
          (else
	     (let ((half (truncate (/ (length a) 2))))
		  (merge (merge-sort (left-n a half))
		         (merge-sort (skip-n a half))))))) 
