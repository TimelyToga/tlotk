using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Asteroid2D : MonoBehaviour {

	public List<GameObject> tiles = new List<GameObject> ();
	private float[] bounds = {0.4f, 0.3f, 0.27f, 0.03f};

	public Transform player;
	public float SCALE = 50.0f;

	private Vector3 center;


	private float FADE_RANGE = 100.0f;
	private float MAX_RANGE = 250.0f;
	private float FADE_START;
	public int WIDTH = 10;
	public int HEIGHT = 12;
	public GameObject[] mTiles;

	GameObject pickTile() {
		float r = Random.value;
		for(int a = 0; a < bounds.Length; a++) {
			if(r <= bounds[a]) {
				return tiles[a];
			}
			r -= bounds[a];
		}

		return tiles[0];
	}

	// Use this for initialization
	void Start () {
		FADE_START = MAX_RANGE - FADE_RANGE;
		mTiles = new GameObject[WIDTH * HEIGHT];

		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				int i = x + y * WIDTH;
				mTiles[i] = Instantiate (pickTile());
				mTiles [i].transform.SetParent (this.transform);
				mTiles[i].transform.position = new Vector3 (50 * x, 50 * y, 0);
			}
		}
		for (int a = 0; a < mTiles.Length; a++) {
			
		}

		center = new Vector3 ((WIDTH * 50) / 2.0f, (HEIGHT * 50) / 2.0f, 0) + transform.position;
	}

	// Update is called once per frame
	void Update () {
		// scan (player.position);
	}

	void scan(Vector3 position) {
		for (int a = 0; a < mTiles.Length; a++) {
			GameObject cur = mTiles [a];
			Tile tile = cur.GetComponent<Tile> ();
			Vector3 dist = position - cur.transform.position;
			if (dist.magnitude < MAX_RANGE) {
				if (dist.magnitude > FADE_START) {
					float curOpacity = 1.0f - (dist.magnitude - FADE_START) / FADE_RANGE;
					tile.setTileOpacity (curOpacity);
				}
			} else {
				tile.setTileOpacity (0.0f);
			}
		}
	}

	public GameObject getTileGO(int x, int y) {
		return mTiles [x + y * WIDTH];
	}

	public Tile getTile (int x, int y){
		return getTileGO (x, y).GetComponent<Tile>();
	}

	public Tile positionToTile(float x, float y) {
		Vector3 offset = transform.position;
		x -= offset.x;
		y -= offset.y;

		int xCoord = ((int) x + 25) / 50;
		int yCoord = ((int) y + 25) / 50;

		return getTile (xCoord, yCoord);
	}

	/*
	 * x & y are the minimum minimum coordinates of the object
	 */
	public List<Tile> tilesUnder(float x, float y, float width, float height) {
		return new List<Tile> ();
	}
}
