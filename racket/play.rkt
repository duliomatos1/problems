#lang racket
(require data/queue)

(define-syntax-rule (vec-ref-map! (vec i) fun)
  (vector-set! vec i (fun (vector-ref vec i))))
(define-syntax-rule (vec-ref-mul! (vec i) n)
  (vector-set! vec i (* n (vector-ref vec i))))
(define-syntax-rule (vec-ref-inc! (vec i) n)
  (vector-set! vec i (+ n (vector-ref vec i))))
(define-syntax-rule (vec-ref-dec! (vec i) n)
  (vector-set! vec i (- (vector-ref vec i) n)))

(define value car)
(define left cadr)
(define right caddr)

(define tree1 '(3
                (4 () ())
                (1
                 ()
                 (5
                  (1 () ())
                  (2 () ())))))

(define tree2 '(F
                 (B
                   (A () ())
                   (D
                     (C () ())
                     (E () ())))
                 (G
                   ()
                   (I
                     (H () ())
                     ()))))

(define (dfs-in-order tree fun)
  (match tree
    [(list v l r)
     (dfs-in-order l fun)
     (fun v)
     (dfs-in-order r fun)]
    [else (void)]))

(define (dfs-in-reverse-order tree fun)
  (match tree
    [(list v l r)
     (dfs-in-reverse-order r fun)
     (fun v)
     (dfs-in-reverse-order l fun)]
    [else (void)]))

(define (dfs-pre-order tree fun)
  (match tree
    [(list v l r)
     (fun v)
     (dfs-pre-order l fun)
     (dfs-pre-order r fun)]
    [else (void)]))

(define (dfs-post-order tree fun)
  (match tree
    [(list v l r)
     (dfs-post-order l fun)
     (dfs-post-order r fun)
     (fun v)]
    [else (void)]))

(define (bfs tree visit)
  (define q (make-queue))
  (enqueue! q tree)
  (define (loop)
    (match (dequeue! q)
      [(list) (void)]
      [(list v l r)
       (visit v)
       (if (pair? l) (enqueue! q l) #f)
       (if (pair? r) (enqueue! q r) #f)
       (if (non-empty-queue? q) (loop) #f)]))
  (loop))


