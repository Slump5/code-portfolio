# Group Docker Project

## Overview
This is a Docker-based distributed system deployment for a midterm project. It sets up containers for NGINX (as a reverse proxy), Spark (for data processing), and Rust (for client-side querying). The system is designed to run on a VPS, with connectivity to a Google Cloud Storage (GCS) data bucket using Delta Lake for data access. Containers communicate internally via a Docker network, and a simple client-side query demonstrates inter-container communication (Rust querying NGINX, which proxies to Spark). The project includes setup scripts, Dockerfiles, configurations, and documentation for installation, building, running, and testing. It also features a Jupyter notebook, text scripts for bucket access, a PowerPoint presentation outlining implementation steps, and a video demo (docker-project-video-demo.mkv). The system handles a sample CSV dataset from the GCS bucket and supports basic HTTP requests for verification.

## Features
- **Docker Container Setup:** Defines and runs three containers: NGINX for proxying, Spark for data processing, and Rust for client-side querying.
- **Inter-Container Communication:** Establishes connectivity via a shared Docker network; Rust sends requests to NGINX, which forwards to Spark.
- **Data Bucket Access:** Uses Delta Lake with Spark to read data from a GCS bucket (e.g., sample_data.csv), including authentication via service account key.
- **NGINX Proxy Configuration:** Routes requests to Spark and handles basic HTTP responses.
- **Rust Client:** Simple Rust application that makes HTTP requests to NGINX and prints responses.
- **Spark Data Processing:** Loads and displays CSV data from GCS using PySpark and Delta Spark.
- **Testing and Demo:** Curl commands for verifying connectivity; Jupyter notebook for bucket access demo; PowerPoint for step-by-step implementation guide; video demo (docker-project-video-demo.mkv, 5-10 minutes).
- **Documentation Support:** Includes instructions, PowerPoint slides with screenshots, and code comments with author names.
- **Simple Query Support:** Client-side query (via Rust or curl) that triggers communication between containers, e.g., fetching a hello message or data preview.
- **Error Handling:** Basic status code checks in requests; console outputs for debugging.

## File Structure
- **instructions.txt:** Project requirements, including Docker installation, container definitions, connectivity, communication, querying, and submission guidelines.
- **Data_Bucket_access (1).ipynb:** Jupyter notebook for installing packages, creating Spark session, uploading GCS key, testing NGINX proxy, and reading sample CSV from GCS bucket.
- **Data_bucket_access.txt:** Text version of the notebook code for GCS bucket access, Spark setup, and simple requests.
- **docker-project-powerpoint.pptx:** PowerPoint presentation with slides on implementation steps, Docker network creation, container building, configurations, testing, and Delta Lake connectivity (includes embedded images: image1.png to image19.png).
- **docker-project-video-demo.mkv:** Video demo (5-10 minutes) showcasing build, run, and testing steps.
- **Dockerfile.txt (Spark):** Dockerfile for Spark container, copying app.py and setting entrypoint for Spark-submit.
- **Dockerfile.txt (Rust):** Dockerfile for Rust container, building the application and running the release binary.
- **Cargo.toml.txt:** Rust project configuration with dependencies (reqwest, tokio, serde_json).
- **main.rs.txt:** Rust source code for printing a message and making an HTTP request to NGINX.
- **Dockerfile.txt (NGINX):** Dockerfile for NGINX container, copying custom nginx.conf.
- **nginx.conf.txt:** NGINX configuration for worker processes, events, and proxying to Spark container.
- **app.py:** (Referenced in Spark Dockerfile; assumed to contain Spark application logic, e.g., data processing).

## Requirements
- Docker (latest version) installed on a VPS or local machine
- Google Cloud account with a GCS bucket (my-midterm-project-bucket) and service account key (key.json)
- Python 3 with Jupyter (for notebook) or basic shell for text scripts
- Rust toolchain (for building Rust container)
- Standard libraries and packages: PySpark, Delta-Spark, GCSFS, Google-Cloud-Storage (installed via pip in notebook)
- Input data: sample_data.csv in GCS bucket
- Optional: PowerPoint viewer for .pptx, video player for .mkv, PDF reader if exporting docs
- Hadoop GCS connector JAR (downloaded in scripts)

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Prepare files: Ensure all Dockerfiles, configs, and source files are in the appropriate directories (Rust files in a subdirectory with Cargo.toml and main.rs).
3. Rename docker files to Dockerfile.nginx, Dockerfile.spark, and Dockerfile.rust.
4. Build Docker images:
	- For NGINX:
		```bash
		docker build -t nginx-container -f Dockerfile.nginx .```
	- For Spark:
		```bash
		docker build -t spark-container -f Dockerfile.spark .```
	- For Rust:
		```bash
		docker build -t rust-container -f Dockerfile.rust .```
5. Create Docker network:
	```bash
	docker network create my-network```
6. Run containers (attach to network):
	- NGINX:
		```bash
		docker run -d --name nginx_container --network my-network -p 80:80 nginx-container```
	- Spark:
		```bash
		docker run -d --name spark_container --network my-network spark-container```
	- Rust:
		```bash
		docker run --name rust_container --network my-network rust-container```
7. For GCS access: Run the Jupyter notebook or text script to set up Spark session and test bucket connectivity (requires key.json upload).

## How to Use
1. Ensure Docker is installed on your VPS and containers are built/running as above.
2. Test inter-container communication:
	- From host: Use curl to query NGINX (proxies to Spark):
		```bash
		curl http://localhost:80``` Should return a hello message or Spark response
	- Run Rust container to see it query NGINX internally.
3. Access GCS bucket:
	- In a Python environment or container: Run the code from Data_bucket_access.txt or notebook to create Spark session, authenticate, and read sample_data.csv:
		```python
		df = spark.read.csv("gs://my-midterm-project-bucket/sample_data.csv", header=True)
		df.show()```
4. Simple client query: Use Rust container logs or curl to send a request that involves all containers (e.g., Rust -> NGINX -> Spark).
5. View logs for debugging:
	```bash
	docker logs <container-name>```
6. For demo: Play docker-project-video-demo.mkv to view the recorded demo (5-10 minutes) showing build/run steps, curl tests, and data access.
7. Submission: Upload source code, setups, documentation (PPT), and unzipped video (docker-project-video-demo.mkv) to D2L; include author names in code comments.

## Project Notes
- **Container Connectivity:** Uses a custom Docker network (my-network); container names (nginx_container, spark_container) are used in configs for resolution.
- **Delta Lake Integration:** Spark session configured with Delta Core and GCS connector for reading Delta-formatted data from GCS.
- **Rust Request:** Makes a GET to http://nginx_container:80; assumes NGINX is reachable internally.
- **NGINX Proxy:** Forwards all root path requests to Spark on port 8080.
- **Data Sample:** CSV with columns Name, Age, Occupation; loaded and displayed via Spark.
- **Authentication:** Uses key.json for GCS access; authenticate via Google Colab or similar for notebook.
- **Testing:** Curl for HTTP status and content; Spark show() for data verification.
- **VPS IP:** Notebook uses http://myip for NGINX; replace with your VPS IP.
- **Performance:** Basic setup for demo; suitable for small datasets.
- **Dependencies:** Assumes standard ports (80 for NGINX, 8080 for Spark); primary data access via gs:// URI.
- **Documentation:** PPT includes screenshots of steps; code has comments with authors.
- **Limitations:** No advanced error recovery; assumes containers start in order (NGINX/Spark before Rust).

## Future Improvements
- Add Docker Compose for easier multi-container orchestration.
- Implement more complex queries (Spark SQL processing returned via API).
- Support dynamic scaling with Docker Swarm or Kubernetes.
- Add monitoring (Prometheus) for container health.
- Enhance Rust app with async requests and JSON parsing.
- Automate key.json handling with environment variables.
- Create a full user guide PDF and automated test scripts.
- Integrate CI/CD for building/pushing images to a registry.

## License
This project is for educational and personal use. Retain the copyright notice: "Brady Theisen, Thomas Hoerger, Jake Cronk - Copyright © 2024 Group Docker Project".
