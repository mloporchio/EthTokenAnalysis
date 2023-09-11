package builder;

import java.util.Objects;

public class Edge implements Comparable<Edge> {
	public final int u;
	public final int v;
	
	public Edge(int u, int v) {
		this.u = u;
		this.v = v;
	}
	
    @Override
    public int hashCode() {
        return Objects.hash(this.u, this.v);
    }
    
    @Override
    public boolean equals(Object o) {
        if (!(o instanceof Edge)) return false;
        if (o == this) return true;
        Edge e = (Edge) o;
        return (this.u == e.u && this.v == e.v);
    }

	@Override
	public int compareTo(Edge o) {
		int s = Integer.compare(this.u, o.u);
		return ((s != 0) ? s : Integer.compare(this.v, o.v));
	}
}
