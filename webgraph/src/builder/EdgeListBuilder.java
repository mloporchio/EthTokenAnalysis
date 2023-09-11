package builder;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

public class EdgeListBuilder {
	public static int nextId = 0;
	public static Map<Integer,Integer> nodes = new HashMap<>();
	public static Set<Edge> edges = new TreeSet<>();
	
	public static void main(String[] args) {
		if (args.length < 2) {
			System.err.println("Usage: EdgeListBuilder <inputFile> <outputFile>");
			System.exit(1);
		}
		final String inputFile = args[0];
		final String outputFile = args[1];
		try (
			BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(inputFile)));
			PrintWriter out = new PrintWriter(outputFile);
		) {
			String line = null;
			while ((line = in.readLine()) != null) {
				String[] parts = line.split(",");
				int u = getOrCreateId(Integer.parseInt(parts[2]));
				int v = getOrCreateId(Integer.parseInt(parts[3]));
				edges.add(new Edge(u, v)); 
			}
			for (Edge e : edges) out.printf("%d\t%d\n", e.u, e.v);
		}
		catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
	
	public static int getOrCreateId(int x) {
        Integer id = nodes.get(x);
        if (id == null) {
            id = nextId;
            nodes.put(x, nextId);
            nextId++;
        }
        return id;
    }

}