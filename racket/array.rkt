; array procedures to implement simple compound changes
; available in other languages
(define-syntax-rule (vec-ref-map! (vec i) fun)
  (vector-set! vec i (fun (vector-ref vec i))))
(define-syntax-rule (vec-ref-mul! (vec i) n)
  (vector-set! vec i (* n (vector-ref vec i))))
(define-syntax-rule (vec-ref-add! (vec i) n)
  (vector-set! vec i (+ n (vector-ref vec i))))
(define-syntax-rule (vec-ref-sub! (vec i) n)
  (vector-set! vec i (- (vector-ref vec i) n)))
