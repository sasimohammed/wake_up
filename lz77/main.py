def encode_lz77(input_string, window_size, lookahead_size):
    out = []
    n = len(input_string)
    i = 0

    while i < n:
        search_start = max(0, i - window_size)
        best_offset = 0
        best_length = 0
        first_char = input_string[i]

        for j in range(search_start, i):
            if input_string[j] != first_char:
                continue

            length = 0
            max_match = min(i - j, lookahead_size, n - i)

            while length < max_match and input_string[j + length] == input_string[i + length]:
                length += 1

            if length > best_length:
                best_length = length
                best_offset = i - j

        if best_length == 0:
            out.append({'offset': 0, 'length': 0, 'next': input_string[i]})
            i += 1
        else:
            next_char = input_string[i + best_length] if i + best_length < n else '\0'
            out.append({'offset': best_offset, 'length': best_length, 'next': next_char})
            i += best_length + 1

    return out


def decode_lz77(tokens):
    out = []
    for token in tokens:
        if token['offset'] == 0 and token['length'] == 0:
            if token['next'] != '\0':
                out.append(token['next'])
        else:
            start = len(out) - token['offset']
            for k in range(token['length']):
                out.append(out[start + k])
            if token['next'] != '\0':
                out.append(token['next'])

    return ''.join(out)


def main():
    while True:
        print("\n" + "=" * 40)
        print("      LZ77 COMPRESSION TOOL")
        print("=" * 40)
        print("1. Compress Text")
        print("2. Decompress Text")
        print("3. Test with Sample Strings")
        print("4. Exit")
        print("=" * 40)

        choice = input("Enter your choice (1-4): ").strip()

        if choice == '1':
           
            s = input("Enter text to compress: ")

           
            try:
                window_input = input("Enter window size (default = 30): ").strip()
                lookahead_input = input("Enter lookahead buffer size (default = 40): ").strip()

                WINDOW_SIZE = int(window_input) if window_input else 30
                LOOKAHEAD_SIZE = int(lookahead_input) if lookahead_input else 40
            except ValueError:
                print("Invalid number! Using default values.")
                WINDOW_SIZE = 30
                LOOKAHEAD_SIZE = 40

            tokens = encode_lz77(s, WINDOW_SIZE, LOOKAHEAD_SIZE)

            print("\nCompressed tokens (offset, length, next):")
            for i, token in enumerate(tokens):
                print(f"{i}: ({token['offset']}, {token['length']}, ", end="")
                if token['next'] == '\0':
                    print("EOF)")
                else:
                    print(f"'{token['next']}')")

        elif choice == '2':
           
            print("\nEnter tokens in format: offset,length,next")
            print("Example: 0,0,A  or  5,3,B  or  10,5,EOF")
            print("Type 'done' when finished:")

            tokens = []
            while True:
                token_input = input("Token: ").strip()
                if token_input.lower() == 'done':
                    break

                try:
                    parts = token_input.split(',')
                    if len(parts) == 3:
                        offset = int(parts[0])
                        length = int(parts[1])
                        next_char = parts[2]

                        if next_char == 'EOF':
                            next_char = '\0'

                        tokens.append({'offset': offset, 'length': length, 'next': next_char})
                    else:
                        print("Invalid format! Use: offset,length,next")
                except ValueError:
                    print("Invalid numbers!")

            if tokens:
                decoded = decode_lz77(tokens)
                print(f"\nDecompressed text: {decoded}")

        elif choice == '3':
         
            test_strings = [
                "ABABABA",
                "ABCABCABC",
                "AAAAA",
                "HelloHelloHello"
            ]

            print("\nTesting compression with sample strings:")
            print("-" * 50)

            for s in test_strings:
                tokens = encode_lz77(s, 30, 40)
                decoded = decode_lz77(tokens)
                status = "✓ PASS" if decoded == s else "✗ FAIL"
                print(f"'{s}' -> {len(tokens)} tokens {status}")

        elif choice == '4':
            print("Goodbye!")
            break

        else:
            print("Invalid choice! Please enter 1-4.")


if __name__ == "__main__":
    main()

