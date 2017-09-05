using UnityEngine;

namespace UnityStandardAssets.Utility
{
	public class SmoothFollow : MonoBehaviour
	{

		public float ZOOM_DAMP = 0.5f;
		public float minZoom = 10.0f;
		public float maxZoom = 100.0f;
		public float CAMERA_FOLLOW_DAMP = 0.15f;
		private Vector3 camVelocity = Vector3.zero;

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
			// Will be +/- depending on the scroll direction
			float scrollAmount = Input.GetAxis("Mouse ScrollWheel");
			float scrollPercentage = 1 + scrollAmount * ZOOM_DAMP;
			float nextZ = Camera.main.transform.position.z * scrollPercentage;

			Vector2 twoDCameraPos = new Vector2 (0, 0);
			// Follow the man 
			if (target) {
				Vector3 targetPos = Camera.main.WorldToScreenPoint (target.position);
				Vector3 delta = target.position - Camera.main.ScreenToWorldPoint (new Vector3 (0.5f, 0.5f, 0.0f));
				Vector3 cameraDestination = Camera.main.transform.position + delta;
				Vector3 newPos = Vector3.SmoothDamp(Camera.main.transform.position,
													cameraDestination,
													ref camVelocity,
													CAMERA_FOLLOW_DAMP);
				twoDCameraPos.x = newPos.x;
				twoDCameraPos.y = newPos.y;
			}
				

			Camera.main.transform.position = new Vector3(twoDCameraPos.x, twoDCameraPos.y, nextZ);
		}
	}
}