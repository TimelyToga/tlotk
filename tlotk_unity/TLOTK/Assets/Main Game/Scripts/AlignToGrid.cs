using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AlignToGrid : MonoBehaviour {

	public float offAmt = 50.0f;
	private float half;

	void Start() {
		half = offAmt / 2.0f;
	}

	public Vector3 getAligned(Vector3 input) {
		Vector3 offset = (transform.position - input);
		offset.x = (offset.x % offAmt) + half;
		offset.y = (offset.y % offAmt) + half;
		offset.z = 0.0f;
		return input + offset;
	}
}

