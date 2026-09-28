# Comprehensive Artificial Intelligence (AI) Notes
*From Foundations to Modern Generative AI, LLMs, and Practical Tools*

---

## 1. What is Artificial Intelligence?

Artificial Intelligence (AI) is the branch of computer science focused on creating systems capable of performing tasks that typically require human cognition—such as reasoning, visual perception, decision-making, natural language understanding, and continuous learning from experience.

### The AI Hierarchy
A standard mental model places modern AI concepts in concentric layers:

```
┌────────────────────────────────────────────────────────┐
│ Artificial Intelligence (AI)                           │
│  ┌──────────────────────────────────────────────────┐  │
│  │ Machine Learning (ML)                            │  │
│  │  ┌────────────────────────────────────────────┐  │  │
│  │  │ Deep Learning (DL)                         │  │  │
│  │  │  ┌──────────────────────────────────────┐  │  │  │
│  │  │  │ Generative AI & LLMs                 │  │  │  │
│  │  │  │ (GPT, Gemini, Claude, Diffusion)    │  │  │  │
│  │  │  └──────────────────────────────────────┘  │  │  │
│  │  └────────────────────────────────────────────┘  │  │
│  └──────────────────────────────────────────────────┘  │
└────────────────────────────────────────────────────────┘
```

- **Artificial Intelligence (Broadest)**: Any machine technique that mimics human intelligence, including symbolic logic, expert systems, heuristic search algorithms (e.g., A*), and statistical models.
- **Machine Learning (Subset)**: Statistical algorithms that automatically improve and identify patterns directly from data without having every rule manually hardcoded.
- **Deep Learning (Subset of ML)**: Neural networks containing multiple hidden layers that autonomously extract hierarchical feature representations (e.g., edges $\to$ textures $\to$ object parts $\to$ full objects).
- **Generative AI (Subset of DL)**: Models designed to produce novel data artifacts (text, code, photorealistic images, audio, video) rather than simply classifying or scoring existing inputs.

### Stages of AI Capability
1. **Artificial Narrow Intelligence (ANI)**: Specialized in designated single domains (e.g., AlphaFold, facial recognition, Siri, chess engines, and current LLMs). Every deployed system today is ANI.
2. **Artificial General Intelligence (AGI)**: Hypothetical machine intelligence matching human-level cognitive adaptability across virtually all intellectual disciplines.
3. **Artificial Superintelligence (ASI)**: Hypothetical AI far exceeding the collective intelligence of humanity across science, creativity, social skills, and wisdom.

---

## 2. Machine Learning Foundations

Traditional software programming takes **Rules + Data** to produce **Answers**. Machine learning flips this paradigm: it takes **Data + Answers** to deduce the underlying **Rules** (parameters $\theta$).

### The Three Core Paradigms

| Paradigm | Objective | Example Tasks | Common Algorithms |
| :--- | :--- | :--- | :--- |
| **Supervised Learning** | Model learns mapping $f(X) \to y$ from labeled ground truth pairs. | Spam detection, house price prediction, object classification | Linear/Logistic Regression, Decision Trees, Random Forests, XGBoost, Support Vector Machines (SVM) |
| **Unsupervised Learning** | Model finds inherent structure, distribution, or patterns without labels ($X$ only). | Customer segmentation, feature reduction, anomaly detection | K-Means Clustering, DBSCAN, Principal Component Analysis (PCA), t-SNE, Autoencoders |
| **Reinforcement Learning (RL)**| An agent learns optimal policy $\pi(s)$ via trial-and-error by collecting rewards/penalties in an environment. | Robotics, chess/Go, self-driving cars, RLHF alignment for LLMs | Q-Learning, Deep Q-Networks (DQN), Proximal Policy Optimization (PPO), Actor-Critic |

### Key Machine Learning Concepts
- **Loss Function ($\mathcal{L}$)**: Measures error between predicted output $\hat{y}$ and true target $y$.
  - *Regression*: Mean Squared Error ($\text{MSE} = \frac{1}{n}\sum (y_i - \hat{y}_i)^2$).
  - *Classification*: Binary Cross-Entropy / Categorical Cross-Entropy.
- **Gradient Descent**: Iteratively updates model parameters $\theta$ to minimize the loss function:
  $$\theta \leftarrow \theta - \eta \nabla_\theta \mathcal{L}(\theta)$$
  where $\eta$ is the learning rate.
- **Bias-Variance Tradeoff**:
  - **High Bias (Underfitting)**: Model is overly rigid and fails to capture genuine relationships in the data.
  - **High Variance (Overfitting)**: Model memorizes training noise and fails to generalize to fresh, unseen data.
  - *Remedies*: Regularization ($L_1$/Lasso, $L_2$/Ridge, Dropout), data augmentation, early stopping, cross-validation.
- **Data Splitting**: Standard dataset split is typically **Train** (70–80%), **Validation** (10–15% for hyperparameter tuning), and **Test** (10–15% for final unbiased evaluation).

---

## 3. Deep Learning & Neural Networks

Deep Learning eliminates the need for manual feature engineering by feeding raw data into stacked layers of artificial neurons.

### Core Building Blocks
1. **The Artificial Neuron**:
   Computes a weighted sum of inputs plus bias, passing through an activation function $\sigma$:
   $$z = \sum_{i=1}^n w_i x_i + b, \quad a = \sigma(z)$$
2. **Activation Functions**: Enable the network to approximate complex non-linear functions (Universal Approximation Theorem).
   - **ReLU ($\max(0, x)$)**: Efficient and prevents vanishing gradients for positive inputs; default for hidden layers.
   - **GELU ($x \cdot \Phi(x)$)**: Smooth probabilistic variant of ReLU; dominant in modern Transformers (BERT, GPT, Claude).
   - **Sigmoid ($\frac{1}{1 + e^{-x}}$)**: Maps outputs to range $(0, 1)$; suited for binary classification outputs.
   - **Softmax ($\frac{e^{z_i}}{\sum_j e^{z_j}}$)**: Converts raw logit scores into a normalized probability distribution across multiple classes.
3. **Backpropagation**:
   Application of the mathematical Chain Rule to compute the partial derivative $\frac{\partial \mathcal{L}}{\partial w}$ for each weight, propagating error signals backwards through the network.
4. **Optimizers**:
   - **SGD (Stochastic Gradient Descent)**: Basic gradient step per mini-batch.
   - **Adam / AdamW**: Uses running averages of both first-order gradients (momentum) and second-order squared gradients (adaptive learning rates); AdamW decouples weight decay and is the gold standard for training modern neural networks.

### Major Neural Architectures
- **Feedforward / MLPs**: Fully-connected dense layers.
- **CNNs (Convolutional Neural Networks)**: Exploit translation invariance via local filters and pooling; king of image tasks (ResNet, EfficientNet).
- **RNNs / LSTMs**: Process sequences step-by-step maintaining hidden states; largely replaced by Transformers for language and sequence modeling due to lack of parallelism.
- **Transformers**: State-of-the-art across natural language, multimodal data, and vision.

---

## 4. Transformers & Large Language Models (LLMs)

Introduced in the 2017 landmark paper *"Attention Is All You Need"* (Vaswani et al.), Transformers replaced sequential recurrence with parallel self-attention.

### The Self-Attention Mechanism
Allows each word/token to weigh the relevance of all other tokens in the sequence simultaneously:

$$\text{Attention}(Q, K, V) = \text{softmax}\left(\frac{QK^T}{\sqrt{d_k}}\right)V$$

- **Query ($Q$)**: What this token is searching for.
- **Key ($K$)**: What properties this token offers.
- **Value ($V$)**: The actual content or information carried by the token.
- **Scaling Factor ($\sqrt{d_k}$)**: Prevents dot products from exploding into regions where Softmax gradients vanish.
- **Multi-Head Attention (MHA)**: Divides dimensions into parallel attention "heads," allowing the model to simultaneously capture grammar, context, syntax, and entity relations.

### Architectural Flavors
| Type | Characteristics | Primary Use Cases | Popular Models |
| :--- | :--- | :--- | :--- |
| **Encoder-Only** | Bidirectional attention (sees left and right context simultaneously). | Text classification, embedding generation, NER, search ranking | BERT, RoBERTa, DeBERTa |
| **Decoder-Only** | Autoregressive with causal masking (each token attends only to previous tokens). | Text generation, code generation, reasoning, conversation | GPT-4o, Claude 3.5, Gemini, LLaMA 3, Mistral |
| **Encoder-Decoder** | Separate encoder and autoregressive decoder. | Translation, abstractive summarization, sequence conversion | T5, BART |

### The Modern LLM Lifecycle
1. **Pre-training (Next-Token Prediction)**:
   - Trained on trillions of text tokens from the open web, books, and code.
   - Learns language, world facts, grammar, and reasoning patterns.
   - Result: *Base Model* (great at autocompletion, but not a chatbot).
2. **Supervised Fine-Tuning (SFT)**:
   - Trained on tens of thousands of high-quality conversational prompt-response pairs.
   - Result: *Instruction-Tuned Model* (answers questions directly).
3. **Alignment (RLHF & DPO)**:
   - **RLHF (Reinforcement Learning from Human Feedback)**: Trains a reward model based on human preference comparisons, fine-tuning the LLM with PPO to maximize helpfulness and minimize harm.
   - **DPO (Direct Preference Optimization)**: Achieves alignment mathematically without training a separate reward model.

---

## 5. Generative AI & Modern Paradigms

### Retrieval-Augmented Generation (RAG)
LLMs have fixed knowledge cutoffs and can hallucinate plausible untruths. RAG bridges internal parametric knowledge with external non-parametric live data:

```
User Query ──► Compute Vector Embedding ──► Vector Database (ANN Search)
                                                    │
                                                    ▼
Prompt: "Context: [Retrieved Documents] \n Question: [Query]" ──► LLM ──► Accurate Answer
```

- **Vector Embeddings**: Dense numerical vectors representing semantic meaning (e.g., text-embedding-3-small, BGE).
- **Vector Databases**: Specialized indexes for rapid approximate nearest neighbor search (e.g., Chroma, Pinecone, Qdrant, Milvus, pgvector).
- **Reranking**: Secondary cross-encoder model that scores retrieved candidate chunks to surface the highest quality context to the LLM.

### AI Agents & Function Calling
An **Agent** combines an LLM with memory, planning, and external execution tools:
- **Tool Calling / Function Calling**: Model emits structured JSON indicating function name and arguments (e.g., `{"name": "fetch_weather", "args": {"city": "Tokyo"}}`), an external runtime executes it, and passes back results.
- **ReAct Framework (Reasoning + Acting)**:
  - *Thought*: Analyze the current problem state.
  - *Action*: Call an API, execute Python code, or search the web.
  - *Observation*: Read the tool output.
  - *Loop* until the objective is accomplished.

### Prompt Engineering Patterns
- **System Prompt**: Set boundaries, persona, and tone ("You are a senior Linux kernel engineer...").
- **Few-Shot Examples**: Give 2–3 input/output examples to anchor output style and accuracy.
- **Chain-of-Thought (CoT)**: Instruct "Think step-by-step before concluding" to dramatically improve multi-step logic.
- **Structured Schema Enforcing**: Demand JSON or Pydantic format for programmatic reliability.

---

## 6. Practical AI Tools & Ecosystem

### Industry Standards Cheat Sheet
- **Core ML Frameworks**:
  - `PyTorch`: Dominant research and production deep learning framework.
  - `JAX`: Accelerated linear algebra from Google, widely used in cutting-edge research.
- **Open-Source Hub**:
  - `Hugging Face`: Model repository (`transformers`, `datasets`, `accelerate`, `diffusers`).
- **Local & Edge Inference**:
  - `Ollama`: Single-command local LLM runner (`ollama run llama3.2`).
  - `llama.cpp`: High-performance C/C++ inference engine for quantized models on CPU / Mac Apple Silicon.
  - `vLLM`: High-throughput production serving with PagedAttention and continuous batching.
- **Agent & RAG Orchestration**:
  - `LangChain` / `LangGraph`: Frameworks for building stateful agent workflows.
  - `LlamaIndex`: Optimized data connectors and retrieval pipelines.
  - `LiteLLM`: Lightweight proxy proxying 100+ LLMs through an OpenAI-compatible format.

### Hands-On Code Snippets

#### 1. Quick Inference with Hugging Face `transformers`
```python
from transformers import pipeline

# Zero-shot classification pipeline
classifier = pipeline("zero-shot-classification", model="facebook/bart-large-mnli")

sequence = "We are releasing a new low-latency database for time-series metrics."
candidate_labels = ["software engineering", "cooking", "astronomy", "finance"]

output = classifier(sequence, candidate_labels)
print(f"Top Label: {output['labels'][0]} ({output['scores'][0]:.2%})")
# Top Label: software engineering (~95%)
```

#### 2. Querying Modern LLMs with Python
```python
import os
from openai import OpenAI

client = OpenAI(api_key=os.environ.get("OPENAI_API_KEY"))

completion = client.chat.completions.create(
    model="gpt-4o",
    messages=[
        {"role": "system", "content": "You are a concise engineering mentor."},
        {"role": "user", "content": "What is the core intuition of self-attention in 2 sentences?"}
    ],
    temperature=0.2,
)

print(completion.choices[0].message.content)
```

---

## 7. Model Evaluation, Limitations & Safety

### Standard AI Benchmarks
- **MMLU (Massive Multitask Language Understanding)**: Evaluates factual knowledge across 57 humanities, STEM, and social science subjects.
- **HumanEval / SWE-bench**: Tests coding problem-solving and solving real GitHub issues.
- **GSM8K / MATH**: Tests grade-school and competition-level mathematical reasoning.
- **Perplexity**: Measures how well a probability distribution predicts a sample (lower is better).

### Core Limitations & Security Risks
1. **Hallucinations**: Generative text can sound authoritative while being factually fabricated.
2. **Context Window Degradation ("Lost in the Middle")**: Models often recall details at the very beginning and very end of prompts better than in the middle.
3. **Prompt Injection**: Malicious user inputs overriding developer system instructions.
4. **Data Contamination**: Benchmark leakage into pre-training corpora inflating perceived model capability.

---

## 8. Essential AI Vocabulary (Cheat Sheet)

| Concept | Definition |
| :--- | :--- |
| **Token** | The basic unit of text an LLM processes (~4 characters or 0.75 words in English). |
| **Logits** | Raw unnormalized output numbers produced by a neural network's final layer. |
| **Temperature** | Softmax hyperparameter: closer to 0 makes outputs focused & deterministic; higher increases randomness. |
| **Quantization** | Compressing model weights (e.g. from 16-bit FP16 to 4-bit INT4) to save VRAM with minimal quality loss. |
| **LoRA** | Low-Rank Adaptation; parameter-efficient fine-tuning (PEFT) training small matrix adapters. |
| **Embeddings** | High-dimensional numerical vectors capturing semantic meaning of words, sentences, or images. |
| **RAG** | Retrieval-Augmented Generation; dynamically injecting real-time documents into prompts. |
| **Agent** | Autonomous software using an LLM as its reasoning engine to select and execute tools. |
