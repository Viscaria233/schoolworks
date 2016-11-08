package udg;

/**
 * Created by Haochen on 2016/10/31.
 */
public class Arc {
    public Node adjVex;

    public Arc(Node adjVex) {
        this.adjVex = adjVex;
    }
    
    @Override
    public String toString() {
    	return "[Arc]" + adjVex;
    }
}
