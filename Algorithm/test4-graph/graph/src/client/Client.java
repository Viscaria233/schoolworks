package client;

import udg.Node;
import udg.UDG;
import udg.VisitMethod;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Haochen on 2016/10/31.
 */
public class Client {
    public static void main(String[] args) {
        List<Node> nodes = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            nodes.add(new Node(i));
        }
        int[][] arcs = {
                {3, 2},
                {3, 2},
                {3},
                {},
                {}
        };
        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = 0; j < arcs[i].length; ++j) {
                nodes.get(i).addArc(nodes.get(arcs[i][j]));
            }
        }
        UDG udg = new UDG(nodes);
        udg.visitMethod = new VisitMethod() {
			@Override
			public void visit(Node node) {
				System.out.print(node.data);
			}
		};
        udg.dfs();
        udg.bfs();
        
        udg.findLink(nodes.get(0), nodes.get(2));
    }
}
