package com.ppapp.geograph3dexample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import com.ppapp.geograph3d.*;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'geograph3d-wrapper' library on application startup.
    static {
        System.loadLibrary("geograph3d-wrapper");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        // Тест
        JGraph graph = new JGraph();
        graph.AddNode(100, "test1", 0.0, 0.0, 0);
        graph.AddNode(200, "test2", 1.0, 1.0, 0);
        graph.AddNode(300, "test3", 2.0, -2.0, 0);

        graph.AddEdge(100, 200);
        graph.AddEdge(200, 100);
        graph.AddEdge(200, 300);
        graph.AddEdge(300, 200);

        JDijkstra dijkstra = new JDijkstra(graph);

        // Поиск пути и вывод
        for(JNode node: dijkstra.FindPath(300, 100, -1, 0.03)) {
            Log.d("GEO", "ID: "+node.GetID());
        }
    }
}
