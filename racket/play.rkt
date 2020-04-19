#lang racket
(require data/queue)
(require racket/contract)

(struct mtree (value left right) #:mutable #:transparent)
(define (make-mtree v)
  (match v
    ['() '()]
    [(list v l r) (mtree v (make-mtree l) (make-mtree r))]))

(define (mtree->list node)
  (match node
    ['() '()]
    [(mtree v l r) (list v (mtree->list l) (mtree->list r))]))

#|   (or/c '() |#
#|         (struct/dc mtree |#
#|                    [value any/c] |#
#|                    [left #:lazy mtree/c] |#
#|                    [right #:lazy mtree/c]))) |#


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

(define tree1 '(3
                (4 () ())
                (1
                 ()
                 (5
                  (1 () ())
                  (2 () ())))))

; wikipedia article example for tree traversal
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

; wikipedia example for BST
(define bst1 '(8
               (3
                (1 () ())
                (6
                 (4 () ())
                 (7 () ())))
               (10
                ()
                (14 (13 () ()) ()))))

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
      ['() (void)]
      [(list v l r)
       (visit v)
       (if (pair? l) (enqueue! q l) #f)
       (if (pair? r) (enqueue! q r) #f)
       (if (non-empty-queue? q) (loop) #f)]))
  (loop))

(define (bst-search node value)
  (match node
    ['() '()]
    [(list v _ _) #:when (= v value) node]
    [(list v l r) (bst-search (if (< value v) l r) value)]))

; not using mutation; inneficient but good for immutability
(define (bst-insert node value)
  (match node
    ['() (list value null null)]
    [(list v _ _) #:when (= v value) node]
    [(list v l r) #:when (< value v)
                  (list-set node 1 (bst-insert l value))]
    [(list v l r) (list-set node 2 (bst-insert r value))]))

; not using mutation
(define (leftmost node)
  (match node
    [(list v '() _) v]
    [(list v l _) (leftmost l)]))
(define (bst-remove node value)
  (define (is-value? v) (= v value))
  (define (recur node)
    (match node
      ['() '()]
      [(list (? is-value?) '() '()) '()]
      [(list (? is-value?) l '()) l]
      [(list (? is-value?) '() r) r]
      [(list (? is-value?) l r) (list-set node 0 (leftmost l))]
      [(list v l r) #:when (< value v)
                    (list-set node 1 (recur l))]
      [(list v l r) (list-set node 2 (recur r))]))
  (recur node))

(define bst2 (make-mtree bst1))

(define (mtree-insert! node value)
  (match node
    ['() (mtree value '() '())]
    [(mtree v _ _) #:when (= v value) (void)]
    [(mtree v '() '())
     (if (< value v)
       (set-mtree-left! node (mtree value '() '()))
       (set-mtree-right! node (mtree value '() '())))]
    [(mtree v '() r) #:when (> value v)
       (set-mtree-right! node (mtree value '() '()))]
    [(mtree v l '()) #:when (< value v)
       (set-mtree-left! node (mtree value '() '()))]
    [(mtree v l r) (mtree-insert! (if (< value v) l r) value)]))

(define (balanced-mtree? node) #f)
