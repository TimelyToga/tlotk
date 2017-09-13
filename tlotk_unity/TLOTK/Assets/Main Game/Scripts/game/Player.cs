using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

	public float rotationSpeed = 1000.0f;
	public float A_MAGN = 10.0f;

	// Vector quantities
	private Vector3 force;
	private Vector3 acceleration;
	private Vector3 velocity;

	public float FORWARD_COEF = 1.0f;
	public float BACKWARD_COEF = 0.5f;

	public float curEnginePower = 1.0f;
	public float SPEED_DECAY = 0.985f;
	public float MASS = 10.0f;
	public float THRUSTER_POWER = 100.0f;

	public GameObject worldTiles;
	 
	// Use this for initialization
	void Start () {
		force = Vector3.zero;
		acceleration = Vector3.zero;
		velocity = Vector3.zero;
	}

	private void powerThrusters() {
		var thrustMagnitude = -1 * Input.GetAxis("Vertical");
		float rot = (transform.eulerAngles.z + 90);
		Vector3 rotVect = new Vector3(Mathf.Cos (Mathf.Deg2Rad * rot), Mathf.Sin(Mathf.Deg2Rad * rot), 0);
		Vector3 thrustVector =  rotVect * thrustMagnitude * THRUSTER_POWER;
	    force = force + thrustVector;
	}
	
	// Update is called once per frame
	void Update () {
		worldTiles.BroadcastMessage ("scan", transform.position);

		// Update engine force
		powerThrusters();

		// Handle physics calculations
		acceleration = force / MASS;
		Vector3 deltaPos = velocity * Time.deltaTime + 0.5f * acceleration * (Time.deltaTime * Time.deltaTime);
		velocity = velocity + (acceleration * Time.deltaTime);
		transform.Translate(deltaPos, Space.World);

        // Zero out force now that it's been applied 
        force = Vector3.zero;
        acceleration = Vector3.zero;
		velocity = velocity * SPEED_DECAY;

		// Rotate player
		var rotation = Input.GetAxis("Horizontal") * Time.deltaTime * rotationSpeed;
        transform.Rotate(0, 0, rotation);

		// var vertical = Input.GetAxis("Vertical") * Time.deltaTime * 100.0f;
        // transform.Translate(0, -vertical, 0);
	}
}
