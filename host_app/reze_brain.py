import random

class RezeBrain:
    def __init__(self):
        # Trực quan các phản hồi theo từng câu nói của người dùng
        self.rules = [
            {
                "keywords": ["chào", "hi", "hello", "lên", "ơi", "dậy"],
                "emotion": "HAPPY",
                "responses": [
                    "Xin chào! Hôm nay bạn thế nào?",
                    "Chào bạn nha! Reze đang nghe đây!",
                    "Hihi, chào buổi tốt nhé!"
                ]
            },
            {
                "keywords": ["xinh", "đẹp", "dễ thương", "yêu", "thích", "cute", "ngọt ngào"],
                "emotion": "SHY",
                "responses": [
                    "E-Hèm... Cảm ơn nhé, bạn làm Reze ngại quá...",
                    "Thật sao? Hè hè... Cảm ơn bạn nha!",
                    "Đừng khen Reze hoài mà... ngượng lắm!"
                ]
            },
            {
                "keywords": ["bom", "nổ", "boom", "bomb", "chainsaw", "biến hình", "chiến"],
                "emotion": "BOMB",
                "responses": [
                    "Ta là Quỷ Bom Reze! BÙM!!! 💣",
                    "Đừng chọc Reze nổ tung đấy nhé!",
                    "Chế độ Bomb Mode đã sẵn sàng!"
                ]
            },
            {
                "keywords": ["ngủ", "mệt", "tối", "khuya", "sleep", "đi ngủ"],
                "emotion": "SLEEPY",
                "responses": [
                    "Oáp... Muộn rồi đó, bạn cũng đi ngủ sớm đi nhé! zZz",
                    "Reze buồn ngủ rồi nè... Chúc bạn ngủ ngon!"
                ]
            },
            {
                "keywords": ["ngốc", "dở", "ghét", "hạ", "xấu"],
                "emotion": "SURPRISED",
                "responses": [
                    "Hả? Bạn vừa nói gì cơ?! 😮",
                    "Này nhá, Reze không giận đâu nhưng đừng chọc nhé!"
                ]
            }
        ]

    def process_input(self, user_text: str):
        text_lower = user_text.lower().strip()
        
        for rule in self.rules:
            for kw in rule["keywords"]:
                if kw in text_lower:
                    response = random.choice(rule["responses"])
                    return rule["emotion"], response
        
        # Mặc định khi nói chuyện thông thường
        default_responses = [
            "Lalala~ Reze nghe thấy rồi nè!",
            "Bạn vừa nói chuyện với Reze đó hả?",
            "Reze luôn ở đây đồng hành cùng bạn!"
        ]
        return "TALKING", random.choice(default_responses)
