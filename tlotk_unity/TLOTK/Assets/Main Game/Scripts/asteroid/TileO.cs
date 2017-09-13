using UnityEngine;
using System.Collections;

[RequireComponent(typeof(SpriteRenderer))]
public class TileO : MonoBehaviour
{
	public GameObject sprite;
	public GameObject stone;
	private SpriteRenderer sRenderer;

	// Use this for initialization
	void Start ()
	{
		sRenderer = sprite.GetComponent<SpriteRenderer> ();
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}

	public void setTileOpacity(float vis) {
		Color newColor = sRenderer.color;
		newColor.a = vis;
		sRenderer.color = newColor;
	}
}

