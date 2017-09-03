using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

	public float rotationSpeed = 150.0f;
	public float acceleration = 10.0f;

	private float velocity;
	private float acceleration;

	// Use this for initialization
	void Start () {
		velocity = new Vector3();
		acceleration = new Vector3();
	}
	
	// Update is called once per frame
	void Update () {
		// Update player location
		Vector3 curDirection = transform.eulerAngles;
		acceleration = curDirection * acceleration;
		var z = Input.GetAxis("Horizontal") * Time.deltaTime * rotationSpeed;
        var y = Input.GetAxis("Vertical") * Time.deltaTime * accelerationSpeed;

        transform.Rotate(0, 0, z);
        transform.Translate(0, -y, 0);
	}
}
