using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class AsteroidGeneration : MonoBehaviour
{
	private int CHUNK_SIZE = 1;
	private int X_SIZE, Y_SIZE;
	private int SQUARE_SIZE = 100;
	private Vector3[] vertices;

	private Mesh mesh;

	private void Awake() {
		Generate ();
	}

	private void Generate() {
		GetComponent<MeshFilter>().mesh = mesh = new Mesh();
		mesh.name = "My First Grid";

		X_SIZE = CHUNK_SIZE;
		Y_SIZE = CHUNK_SIZE;
		vertices = new Vector3[(X_SIZE + 1) * (Y_SIZE + 1)];
		Debug.Log ("Verts have values");
	
		for (int i = 0, y = 0; y <= Y_SIZE; y++) {
			for (int x = 0; x <= X_SIZE; x++, i++) {
				vertices[i] = new Vector3(x * SQUARE_SIZE, y * SQUARE_SIZE);
			}
		}

		mesh.vertices = vertices;

		int[] triangles = new int[X_SIZE * Y_SIZE * 6];
		for (int ti = 0, vi = 0, y = 0; y < Y_SIZE; y++, vi++) {
			for (int x = 0; x < X_SIZE; x++, ti += 6, vi++) {
				triangles[ti] = vi;
				triangles[ti + 3] = triangles[ti + 2] = vi + 1;
				triangles[ti + 4] = triangles[ti + 1] = vi + X_SIZE + 1;
				triangles[ti + 5] = vi + X_SIZE + 2;
			}
		}

		mesh.triangles = triangles;

		transform.Rotate (0, 180, 0);

//		mesh.RecalculateNormals ();
	}

	private void OnDrawGizmos() {
		if (vertices == null) {
			return;
		}

		Gizmos.color = Color.red;
		for (int i = 0; i < vertices.Length; i++) {
			Gizmos.DrawSphere(vertices[i], 1.0f);
		}
	}
}

