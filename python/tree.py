class Tree:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def dfs_inorder(node, visit):
    if not node:
        return
    dfs_inorder(node.left, visit)
    visit(node.value)
    dfs_inorder(node.right, visit)

tree = Tree(5, Tree(3, Tree(1)), Tree(4, None, Tree(7)))

dfs_inorder(tree, lambda x: print(x))
