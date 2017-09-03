using UnityEngine;

namespace UnityStandardAssets.Utility
{
	public class SmoothFollow : MonoBehaviour
	{

		public float zoomDampening = 0.125f;
		public float minZoom = 10.0f;
		public float maxZoom = 100.0f;

		private float scrollAmount = 0.0f; 

		// The target we are following
		[SerializeField]
		private Transform target;
		// The distance in the x-z plane to the target
		[SerializeField]
		private float distance = 10.0f;
		// the height we want the camera to be above the target
		[SerializeField]
		private float height = 5.0f;

		[SerializeField]
		private float rotationDamping;
		[SerializeField]
		private float heightDamping;

		// Use this for initialization
		void Start() { 

		}

		void Update () {
			scrollAmount = scrollAmount + Input.GetAxis("Mouse ScrollWheel");

		    float scrollDirection = scrollAmount * zoomDampening;

		    float frustumHeight = target.localScale.y + scrollDirection;
			float distance = frustumHeight * 0.5f / Mathf.Tan(Camera.main.fieldOfView * 0.5f);

			// Since front side of the block is not at pivot
			distance += target.localScale.z * 0.5f;
			Camera.main.transform.position = new Vector3(0, -1, 0) * distance;
		}
	}
}