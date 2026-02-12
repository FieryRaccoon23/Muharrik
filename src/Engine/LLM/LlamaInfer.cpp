#include "LlamaInfer.h"

#include <string>
#include <EASTL/vector.h>

#include "llama.h"

namespace Muharrik
{
    static void die(const char* msg) 
    {
        std::fprintf(stderr, "%s\n", msg);
        std::exit(1);
    }

    void LlamaInfer::TestLlama()
    {
        const char* model_path = "path/to/model";
        const std::string prompt = "You are a helpful assistant.\nUser: Give me 3 tips to learn C++ faster.\nAssistant:";

        llama_backend_init();

        llama_model_params mparams = llama_model_default_params();
        llama_model* model = llama_model_load_from_file(model_path, mparams);
        const llama_vocab * vocab = llama_model_get_vocab(model);
        if (!model) die("Failed to load model");

        llama_context_params cparams = llama_context_default_params();
        cparams.n_ctx = 2048;
        cparams.n_batch = 512;

        llama_context* ctx = llama_init_from_model(model, cparams);
        if (!ctx) die("Failed to create context");

        // Tokenize prompt
        eastl::vector<llama_token> tokens(prompt.size() + 8);
        int n_prompt = llama_tokenize(vocab, prompt.c_str(), (int)prompt.size(),
                                    tokens.data(), (int)tokens.size(),
                                    /*add_special=*/true, /*parse_special=*/true);
        if (n_prompt < 0) die("Tokenization failed");
        tokens.resize(n_prompt);

        // Evaluate prompt
        llama_batch batch = llama_batch_get_one(tokens.data(), (int)tokens.size());
        if (llama_decode(ctx, batch) != 0)
        {
            die("llama_decode failed on prompt");
        }

        const int max_gen = 128;

        // Simple sampling settings
        llama_sampler* smpl = llama_sampler_chain_init(llama_sampler_chain_default_params());
        llama_sampler_chain_add(smpl, llama_sampler_init_top_k(40));
        llama_sampler_chain_add(smpl, llama_sampler_init_top_p(0.9f, 1));
        llama_sampler_chain_add(smpl, llama_sampler_init_temp(0.7f));
        llama_sampler_chain_add(smpl, llama_sampler_init_dist(LLAMA_DEFAULT_SEED));

        for (int i = 0; i < max_gen; ++i) {
            const llama_token next = llama_sampler_sample(smpl, ctx, -1);

            if (next == llama_token_eos(vocab)) break;

            // Print token text
            char buf[256];
            int n = llama_token_to_piece(vocab, next, buf, sizeof(buf), 0, false);
            if (n > 0) std::fwrite(buf, 1, (size_t)n, stdout);

            // Feed token back in
            llama_token t = next;
            llama_batch batch = llama_batch_get_one(tokens.data(), (int)tokens.size());
            if (llama_decode(ctx, batch) != 0)
            {
                die("llama_decode failed during generation");
            }
        }

        std::fputc('\n', stdout);

        llama_sampler_free(smpl);
        llama_free(ctx);
        llama_model_free(model);
        llama_backend_free();

    }
    
}