package udg;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Haochen on 2016/10/31.
 */
public class UDG {
    public List<Node> nodes;
    public VisitMethod visitMethod;

    public UDG() {
    }

    public UDG(List<Node> nodes) {
        this.nodes = nodes;
    }

    public void dfs() {
        Map<Node, Boolean> visited = new HashMap<>();
        for (Node node : nodes) {
            visited.put(node, false);
        }
        for (Node node : nodes) {
            if (!visited.get(node)) {
                node.dfs(visited, visitMethod, null, null);
            }
        }
        System.out.println();
    }

    public void bfs() {
        Map<Node, Boolean> visited = new HashMap<>();
        for (Node node : nodes) {
            visited.put(node, false);
        }
        for (Node node : nodes) {
            if (!visited.get(node)) {
                node.bfs(visited, visitMethod);
            }
        }
        System.out.println();
    }

    public void findLink(Node node1, Node node2) {
    	if (!nodes.contains(node1) || !nodes.contains(node2)) {
    		return;
    	}
    	Map<Node, Boolean> visited = new HashMap<>();
        for (Node node : nodes) {
            visited.put(node, false);
        }
        
		node1.findLink(visited, node2);
        System.out.println();
    }
}
