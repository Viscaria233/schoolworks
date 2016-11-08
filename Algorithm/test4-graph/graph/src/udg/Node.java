package udg;

import java.util.*;

/**
 * Created by Haochen on 2016/10/31.
 */
public class Node {
    public Object data;
    public List<Arc> arcs = new ArrayList<>();
    
    public VisitMethod visitMethod;
    public OnTargetVisitedListener onLeafVisitedListener;

    public Node(Object data) {
        this.data = data;
    }

    public void addArc(Node node) {
        this.arcs.add(new Arc(node));
        node.arcs.add(new Arc(this));
    }
    
    @Override
    public String toString() {
    	return "[Node]" + data;
    }

    public void dfs(Map<Node, Boolean> visited, VisitMethod visitMethod, OnTargetVisitedListener onTargetVisitedListener, Node target) {
    	if (visitMethod == null) {
    		return;
    	}
        visitMethod.visit(this);
        visited.remove(this);
        visited.put(this, true);
        
		if (target != null && onTargetVisitedListener != null
				&& this.equals(target)) {
			onTargetVisitedListener.onTargetVisited(this);
		}
        for (Arc arc : arcs) {
            if (!visited.getOrDefault(arc.adjVex, true)) {
                arc.adjVex.dfs(visited, visitMethod, onTargetVisitedListener, target);
            }
        }
    }

    public void bfs(Map<Node, Boolean> visited, VisitMethod visitMethod) {
    	if (visitMethod == null) {
    		return;
    	}
        Queue<Node> queue = new LinkedList<>();
        queue.offer(this);
        while (!queue.isEmpty()) {
            Node node = queue.poll();
            if (!visited.get(node)) {
                visitMethod.visit(node);
                visited.remove(node);
                visited.put(node, true);
                for (Arc arc : arcs) {
                    queue.offer(arc.adjVex);
                }
            }
        }
    }
    
    public List<Node> findLink(Map<Node, Boolean> visited, final Node node) {
    	if (arcs.isEmpty()) {
    		return null;
    	}
    	final List<Node> link = new ArrayList<>();
    	link.add(this);

        VisitMethod visitMethod = new VisitMethod() {
			@Override
			public void visit(Node node) {
				link.add(node);
			}
		};
        
        OnTargetVisitedListener onLeafVisitedListener = new OnTargetVisitedListener() {
			@Override
			public void onTargetVisited(Node target) {
				for (Node n : link) {
					System.out.print(n.data);
				}
				System.out.println();
				link.remove(link.size() - 1);
			}
		};
		
		this.dfs(visited, visitMethod, onLeafVisitedListener, node);
    	
    	return link;
    }
}
