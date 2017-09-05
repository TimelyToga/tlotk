using UnityEngine;

[RequireComponent(typeof(MeshFilter), typeof(MeshRenderer))]
public class AsteroidGeneration : MonoBehaviour
{
	public int CHUNK_SIZE = 10;
	private int X_SIZE, Y_SIZE;

	public int SQUARE_SIZE = 50;

	private float RADIUS;
	private Vector3[] vertices;
	private Mesh mesh;

	void Start() {
		Debug.Log ("CREATING");
	}

	private void Awake() {
		Generate ();
	}

	private void Generate() {
		X_SIZE = CHUNK_SIZE;
		Y_SIZE = CHUNK_SIZE;
		RADIUS = X_SIZE;

		float halfX = X_SIZE / 2.0f;
		float halfY = Y_SIZE / 2.0f;

		GetComponent<MeshFilter>().mesh = mesh = new Mesh();
		mesh.name = "My First Grid";

		vertices = new Vector3[(X_SIZE + 1) * (Y_SIZE + 1)];

		for (int i = 0, y = 0; y <= Y_SIZE; y++) {
			for (int x = 0; x <= X_SIZE; x++, i++) {
				vertices[i] = new Vector3(x * SQUARE_SIZE, y * SQUARE_SIZE);
			}
		}

		mesh.vertices = vertices;

		int[] triangles = new int[X_SIZE * Y_SIZE * 6];
		for (int ti = 0, vi = 0, y = 0; y < Y_SIZE; y++, vi++) {
			for (int x = 0; x < X_SIZE; x++, ti += 6, vi++) {
				if (Mathf.Pow((halfX - x), 2) + Mathf.Pow((halfY - y), 2) > RADIUS)
					continue;
				triangles[ti] = vi + X_SIZE + 2;
				triangles[ti + 3] = triangles[ti + 2] = vi + 1;
				triangles[ti + 4] = triangles[ti + 1] = vi + X_SIZE + 1;
				triangles[ti + 5] = vi;
			}
		}

		mesh.triangles = triangles;

		mesh.RecalculateNormals ();
	}
}
